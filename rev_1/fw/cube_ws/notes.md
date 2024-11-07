# Logging and printing
## Adding printf

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