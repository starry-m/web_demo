// Copyright (c) 2024 Cesanta Software Limited
// All rights reserved

#define LED1 PIN('A', 0)
#define LED2 PIN('A', 1)
#define UART_DEBUG NULL

#define BIT(x) (1UL << (x))
#define CLRSET(reg, clear, set) ((reg) = ((reg) & ~(clear)) | (set))
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) (pin >> 8)

// No-op HAL API implementation for a device with GPIO and UART
#define hal_init()
#define hal_ram_free() 0
#define hal_ram_used() 0
#define gpio_output(pin)
#define gpio_toggle(pin)
#define gpio_read(pin) 0
#define gpio_write(pin, val)
#define uart_init(uart, baud) 
#define uart_read_ready(uart) 0
#define uart_write_byte(uart, ch)
#define uart_write_buf(uart, buf, len)
