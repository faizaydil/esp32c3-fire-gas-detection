#ifndef LCD1602_DRIVER_H
#define LCD1602_DRIVER_H

void lcd_init(void);
void lcd_show_status(int temp, int hum, const char *status);

#endif
