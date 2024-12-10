# Configure
## Configure LED
Configure GPIO pin 13 as output

```c
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(1000);
```
## Configuring usb-logging
configure GPIO-pin 9 to gpio output.
- Start as low
- Pull-up after USB is initialized
```c
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
```

### Adding printf

**Using printf**

```c
    uint8_t buffer[] = "LED BLINK\n\r";
    printf("printf send: %d, %.2f\r\n", 30, 21.5541);
```
**Add printf to usb**

Add this to usb_device.c
```c

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


int _write(int file, char *ptr, int len)
{
	int DataIdx;

    CDC_Transmit_FS((uint8_t*)ptr, len);
	// for (DataIdx = 0; DataIdx < len; DataIdx++)
	// {
	// 	__io_putchar(*ptr++);
	// }
	return len;
}
```
Make sure to add to linkerscript:
```c
LDFLAGS += -u _printf_float
```

Alternatively when using cmake add
```cmake
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -u _printf_float)
```
to your CMakeLists.txt

## Configure adc
### Pins
**Sensors**
- MEAS-temp: PB14, ADC4, CH4
- MEAS-bat: PB15, ADC4, CH5

**Voltage feedback**
- PhaseU_DIV: PA2, ADC1, CH3
- PhaseV_DIV: PA5, ADC2, CH2
- PhaseW_DIV: PA6, ADC2, CH3
- Phase-GVIRTUAL: PA1, ADC1, CH2

**Current feedback**
- PhaseU-current: PB13, ADC3, CH5
- PhaseV-current: PB12, ADC4, CH3
- PhaseW-current: PB2, ADC2, CH12

## Configure MCO
### Pins
TIM1
- PhaseU_SW: PA7, CH1N
- PhaseU_SD: PB0, CH2N
- PhaseV_SW: PB1, CH3N

TIM8
- PhaseV_SD: PB6, CH1
- PhaseW_SW: PB5, CH3N
- PhaseW_SD: PB4, CH2N

-> Big mistake already here
- Should have used 
    - U,V,W_SW controlled by a separate advanced timer
    - U,V,W_SD controlled by a separate advanced timer

Instead of intermixing them


## Configure CAN + I2C


# Building and Flashing
## Building
```bash
sudo apt install gcc-arm-none-eabi
```
## Flashing
1. Download stm32-cube programmer.

2. Use the following command to flash the stm32f303, which performs a hardware reset
```bash
$STM32_PRG_PATH/STM32_Programmer_CLI -c port=swd mode=UR -rst -w <path_to_binary> 0x08000000
```
with STM32_PRG_PATH the path to the CLI binary.

In case of issues, perform a flash erase:
```bash
$STM32_PRG_PATH/STM32_Programmer_CLI -c port=swd mode=UR -e all
```

# TODO
## Logging issue
There's an issue where we need some kind-of buffer mechanism for the logger to print and wait so it doesn't reject half the messages it receives on short notice.
One of the best ways would be to introduce a separate logger thread.
However for that we would need to introduce an RTOS, which I would only do after the drivers are fully operational.
SO:
1. Test PWM + generate code
2. Test USART + generate code 
3. Test CAN + generate code
4. Test I2C + generate code

-> Package all this code nicely in some drivers AND add an RTOS on top (FreeRTOS preferably)