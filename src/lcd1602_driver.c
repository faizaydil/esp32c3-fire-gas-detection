#include "lcd1602_driver.h"
#include "driver/i2c.h"
#include "freertos/task.h"
#include <stdio.h>

#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_SDA_IO 9
#define I2C_SCL_IO 10
#define I2C_FREQ_HZ 100000

#define LCD_ADDR 0x27   // change to 0x3F if needed

#define LCD_BACKLIGHT 0x08
#define ENABLE_BIT 0x04
#define RS_BIT 0x01

static void i2c_write(uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (LCD_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, data | LCD_BACKLIGHT, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);
}

static void lcd_pulse_enable(uint8_t data)
{
    i2c_write(data | ENABLE_BIT);
    vTaskDelay(pdMS_TO_TICKS(1));
    i2c_write(data & ~ENABLE_BIT);
    vTaskDelay(pdMS_TO_TICKS(1));
}

static void lcd_send_nibble(uint8_t nibble, uint8_t mode)
{
    uint8_t data = (nibble & 0xF0) | mode;
    lcd_pulse_enable(data);
}

static void lcd_send_byte(uint8_t value, uint8_t mode)
{
    lcd_send_nibble(value & 0xF0, mode);
    lcd_send_nibble((value << 4) & 0xF0, mode);
}

static void lcd_cmd(uint8_t cmd)
{
    lcd_send_byte(cmd, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
}

static void lcd_data(uint8_t data)
{
    lcd_send_byte(data, RS_BIT);
}

void lcd_clear(void)
{
    lcd_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_cmd(0x80 | (col + row_offsets[row]));
}

void lcd_print(const char *str)
{
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_IO,
        .scl_io_num = I2C_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ
    };

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    vTaskDelay(pdMS_TO_TICKS(50));

    lcd_send_nibble(0x30, 0);
    vTaskDelay(pdMS_TO_TICKS(5));
    lcd_send_nibble(0x30, 0);
    vTaskDelay(pdMS_TO_TICKS(1));
    lcd_send_nibble(0x30, 0);
    lcd_send_nibble(0x20, 0);

    lcd_cmd(0x28); // 4-bit, 2-line
    lcd_cmd(0x0C); // display ON
    lcd_cmd(0x06); // entry mode
    lcd_clear();
}

void lcd_show_status(int temp, int hum, const char *status)
{
    char line[17];

    lcd_clear();

    lcd_set_cursor(0, 0);
    snprintf(line, 16, "T:%dC H:%d%%", temp, hum);
    lcd_print(line);

    lcd_set_cursor(0, 1);
    lcd_print(status);
}
