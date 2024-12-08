#include "adc_read.h"
#include <stdint.h>
#include <math.h>



#define TS_CAL1_ADDR       ((uint16_t*)0x1FFFF7B8) // Calibration value at 30°C
#define TS_CAL2_ADDR       ((uint16_t*)0x1FFFF7C2) // Calibration value at 110°C

// * (0x1FFF F7BA, 0x1FFF F7BB)
#define VREFINT_CAL_ADDR   ((uint16_t*)0x1FFFF7BA) // VREFINT calibration value
#define VREF       3.3f   // VREF value (p. 381 user manual)
#define TEMP30_CAL_DEG     30.0f  // Temperature at TS_CAL1
#define TEMP110_CAL_DEG    110.0f // Temperature at TS_CAL2

/**
 * 
 * typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;
 */

/**
 * ADC1_CH2: gvirtual
 * ADC1_CH3: PhaseU_DIV
 * ADC1_VREF
 */

static float VDDA_ref = -1;
#define N_CONVERTS_ADC1  4


void adc1_processing(uint16_t *buff, int buffsize)
{

    // VDDA Calculation
    volatile uint16_t vref_cal = *VREFINT_CAL_ADDR;
    //! WARN: make sure to divide the uint16's as floats.
    VDDA_ref = VREF *  ((float)((float)vref_cal / (float)buff[3]));
    printf("VDDA_ref: %.4f\r\n", VDDA_ref);
}
void adc1_read(ADC_HandleTypeDef *hadc)
{
    char* adc_naming[] = {"gvirt", "U_div", "temp", "vref"};
    int adc_periph=1;

    uint16_t adc_buffer[N_CONVERTS_ADC1] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("[ERR] ADC Start Error\n");
        return;
    }

    for (int i=0; i<N_CONVERTS_ADC1; i++)
    {
        HAL_ADC_PollForConversion(hadc, 1000);
        adc_buffer[i] = HAL_ADC_GetValue(hadc);
    }

    HAL_ADC_Stop(hadc);

    // for (int i=0; i<N_CONVERTS_ADC1; i++)
    // {
    //     printf("ADC%d: %s: %u, ", adc_periph, adc_naming[i], adc_buffer[i]);
    // }
    // printf("\r\n");
    adc1_processing((uint16_t*)adc_buffer, N_CONVERTS_ADC1);
}

/**
 * ADC2_CH2: PhaseV_DIV
 * ADC2_CH3: PhaseW_DIV
 * ADC2_CH12: PhaseW-current
 */

#define N_CONVERTS_ADC2  3
void adc2_read(ADC_HandleTypeDef *hadc)
{
    char* adc_naming[] = {"V_div", "W_div", "W_current"};
    int adc_periph=2;

    uint16_t adc_buffer[N_CONVERTS_ADC2] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("[ERR] ADC Start Error\n");
        return;
    }

    for (int i=0; i<N_CONVERTS_ADC2; i++)
    {
        HAL_ADC_PollForConversion(hadc, 1000);
        adc_buffer[i] = HAL_ADC_GetValue(hadc);
    }

    HAL_ADC_Stop(hadc);

    for (int i=0; i<N_CONVERTS_ADC2; i++)
    {
        printf("ADC%d: %s: %u, ", adc_periph, adc_naming[i], adc_buffer[i]);
    }
    printf("\r\n");
}

#define N_CONVERTS_ADC3  1
void adc3_read(ADC_HandleTypeDef *hadc)
{   
    printf("Entering adc3_read\r\n");
    char* adc_naming[] = {"V_div", "W_div", "W_current"};
    int adc_periph=3;
    
    uint16_t adc_buffer[N_CONVERTS_ADC3] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("[ERR] ADC Start Error\n");
        return;
    }

    for (int i=0; i<N_CONVERTS_ADC3; i++)
    {
        HAL_ADC_PollForConversion(hadc, 1000);
        adc_buffer[i] = HAL_ADC_GetValue(hadc);
    }

    HAL_ADC_Stop(hadc);

    for (int i=0; i<N_CONVERTS_ADC3; i++)
    {
        printf("ADC%d: %s: %u, ", adc_periph, adc_naming[i], adc_buffer[i]);
    }
    printf("\r\n");
}

/**
 * Channel 4: V_current, temperature, vbat
 * ? Temperature
 * We need the temperature as a function of R2
 * 
 */

// * TEMPERATURE
#define THERMISTOR_B    4050.0
#define THERMISTOR_TCAL1 298.15
#define THERMISTOR_RBASE   47.0 //kOhm
#define THERMISTOR_R1   33.0 // kOhm

// * Battery voltage
#define BATTMEAS_RATIO 33.0/(330.0+33.0) // kOhm

void adc4_processing(uint16_t *buff, int buffsize)
{
    // * Temperature calculation using thermistor
    //! Warn: the VDDA_ref here comes from the first adc, we should use the one that is used as input for adc3 and 4.
    float v_temp = VDDA_ref * ((float)((float)buff[1] / (float)0xfff));
    printf("VTEMP: %.2f, %u, %u, %.2f\r\n", v_temp, buff[1], VDDA_ref);

    // Current through primary resistor
    float th_ir1 = (VDDA_ref - v_temp) / THERMISTOR_R1;
    // Divide v_temp / current through primary
    float thermistor_rnew = v_temp / th_ir1;
    // Calculate the temperature based on the 2 resistors
    float T2_val_inv = 1/THERMISTOR_TCAL1 - logf(THERMISTOR_RBASE/thermistor_rnew) / THERMISTOR_B;
    float T2_val = 1/T2_val_inv - 273.15;
    printf("Thermistor_T: %.2f\r\n", T2_val);
    // * VBAT calculation using resistor
    float vbat = (((float)buff[2] / (float)0xfff) * VDDA_ref) / BATTMEAS_RATIO;
    printf("Vbat: %.2f\r\n", vbat);

}

#define N_CONVERTS_ADC4  3
void adc4_read(ADC_HandleTypeDef *hadc)
{
    int adc_periph=4;
    char* adc_naming[] = {"V_current", "TEMP", "VBAT"};


    uint16_t adc_buffer[N_CONVERTS_ADC4] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("[ERR] ADC Start Error\n");
        return;
    }

    for (int i=0; i<N_CONVERTS_ADC4; i++)
    {
        HAL_ADC_PollForConversion(hadc, 1000);
        adc_buffer[i] = HAL_ADC_GetValue(hadc);
    }

    HAL_ADC_Stop(hadc);

    // for (int i=0; i<N_CONVERTS_ADC4; i++)
    // {
    //     printf("ADC%d: %s: %u, ", adc_periph, adc_naming[i], adc_buffer[i]);
    // }
    // printf("\r\n");
    adc4_processing((uint16_t*)adc_buffer, N_CONVERTS_ADC4);
}