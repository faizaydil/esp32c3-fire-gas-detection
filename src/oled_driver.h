#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

void oled_init(void);
void oled_clear(void);
void oled_draw_text(int x, int y, const char *txt);
void oled_update(void);

#endif
