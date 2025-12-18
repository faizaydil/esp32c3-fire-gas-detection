#include "lcd1602_driver.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

#define LCD_RS GPIO_NUM_10
#define LCD_E  GPIO_NUM_11
#define LCD_D4 GPIO_NUM_12
#define LCD_D5 GPIO_NUM_13
#define LCD_D6 GPIO_NUM_14
#define LCD_D7 GPIO_NUM_15

static void lcd_pulse_enable(void)
{
    gpio_set_level(LCD_E, 1);
    esp_rom_delay_us(1);
    gpio_set_level(LCD_E, 0);
    esp_rom_delay_us(100);
}

static void lcd_send_nibble(uint8_t data)
{
    gpio_set_level(LCD_D4, (data >> 0) & 1);
    gpio_set_level(LCD_D5, (data >> 1) & 1);
    gpio_set_level(LCD_D6, (data >> 2) & 1);
    gpio_set_level(LCD_D7, (data >> 3) & 1);
    lcd_pulse_enable();
}

static void lcd_send_byte(uint8_t data, int rs)
{
    gpio_set_level(LCD_RS, rs);
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
}

void lcd_init(void)
{
    gpio_set_direction(LCD_RS, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_E, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D4, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D5, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D6, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_D7, GPIO_MODE_OUTPUT);

    esp_rom_delay_us(50000);
    lcd_send_nibble(0x03);
    lcd_send_nibble(0x02);
    lcd_send_byte(0x28, 0);
    lcd_send_byte(0x0C, 0);
    lcd_send_byte(0x01, 0);
}

void lcd_clear(void)
{
    lcd_send_byte(0x01, 0);
    esp_rom_delay_us(2000);
}

void lcd_print(int row, int col, const char *text)
{
    uint8_t addr = (row == 0) ? 0x80 : 0xC0;
    lcd_send_byte(addr + col, 0);
    while (*text) lcd_send_byte(*text++, 1);
}
