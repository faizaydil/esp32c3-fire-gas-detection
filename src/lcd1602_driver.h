#ifndef LCD1602_DRIVER_H
#define LCD1602_DRIVER_H

#include <stdint.h>

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print(const char *str);
void lcd_show_status(int temp, int hum, const char *status);

#endif
