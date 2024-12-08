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

## Configure adc
### Sensors
- MEAS-temp: PB14
- MEAS-bat: PB15


# Building and Flashing
## Building
```bash
sudo apt install gcc-arm-none-eabi
```
## Flashing
- Download stm32-cube programmer.
- Use command
```bash
$STM32_PRG_PATH/STM32_Programmer_CLI -c port=swd mode=UR -rst -w build/uart_usb.bin 0x08000000
```
with STM32_PRG_PATH the path to the CLI binary.