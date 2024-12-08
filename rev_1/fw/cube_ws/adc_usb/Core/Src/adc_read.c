#include "adc_read.h"
#include <stdint.h>

#define TS_CAL1_ADDR       ((uint16_t*)0x1FFFF7B8) // Calibration value at 30°C
#define TS_CAL2_ADDR       ((uint16_t*)0x1FFFF7C2) // Calibration value at 110°C
#define VREFINT_CAL_ADDR   ((uint16_t*)0x1FFFF7BA) // VREFINT calibration value


#define VREF_TYPICAL       3.3f   // Typical VREF value in volts
#define TEMP30_CAL_DEG     30.0f  // Temperature at TS_CAL1
#define TEMP110_CAL_DEG    110.0f // Temperature at TS_CAL2
#define ADC_RES 4095f

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

#define N_CONVERTS_ADC1  3
void adc1_read(ADC_HandleTypeDef *hadc)
{
    char* adc_naming[] = {"gvirt", "U_div", "vref"};
    int adc_periph=1;

    uint16_t adc_buffer[N_CONVERTS_ADC1] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("ADC Start Error\n");
        return;
    }

    for (int i=0; i<N_CONVERTS_ADC1; i++)
    {
        HAL_ADC_PollForConversion(hadc, 1000);
        adc_buffer[i] = HAL_ADC_GetValue(hadc);
    }

    HAL_ADC_Stop(hadc);

    for (int i=0; i<N_CONVERTS_ADC1; i++)
    {
        printf("ADC%d: %s: %u, ", adc_periph, adc_naming[i], adc_buffer[i]);
    }
    printf("\r\n");
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
        printf("ADC Start Error\n");
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
    char* adc_naming[] = {"V_div", "W_div", "W_current"};
    int adc_periph=3;
    
    uint16_t adc_buffer[N_CONVERTS_ADC3] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("ADC Start Error\n");
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

// SEEMS TO WORK!!!
#define N_CONVERTS_ADC4  3

void adc4_processing(uint16_t *buff)
{
    
}

void adc4_read(ADC_HandleTypeDef *hadc)
{
    int adc_periph=4;
    char* adc_naming[] = {"V_current", "TEMP", "VBAT"};


    uint16_t adc_buffer[N_CONVERTS_ADC4] = {0};
    if (HAL_ADC_Start(hadc) != HAL_OK)
    {
        printf("ADC Start Error\n");
        return;
    }

    for (int i=0; i<N_CONVERTS_ADC4; i++)
    {
        HAL_ADC_PollForConversion(hadc, 1000);
        adc_buffer[i] = HAL_ADC_GetValue(hadc);
    }

    HAL_ADC_Stop(hadc);

    for (int i=0; i<N_CONVERTS_ADC4; i++)
    {
        printf("ADC%d: %s: %u, ", adc_periph, adc_naming[i], adc_buffer[i]);
    }
    printf("\r\n");
}