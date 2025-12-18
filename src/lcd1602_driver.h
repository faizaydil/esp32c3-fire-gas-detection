#ifndef LCD1602_DRIVER_H
#define LCD1602_DRIVER_H

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(int col, int row);
void lcd_print(const char *str);

#endif
