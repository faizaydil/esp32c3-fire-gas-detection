#include "lcd1602_driver.h"
#include "driver/i2c.h"
#include "freertos/task.h"
#include <stdio.h>

#define I2C_NUM I2C_NUM_0
#define SDA_PIN 9
#define SCL_PIN 10
#define LCD_ADDR 0x27

#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04
#define RS 0x01

static void i2c_write(uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (LCD_ADDR << 1), true);
    i2c_master_write_byte(cmd, data | LCD_BACKLIGHT, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);
}

static void pulse(uint8_t data)
{
    i2c_write(data | ENABLE);
    vTaskDelay(pdMS_TO_TICKS(1));
    i2c_write(data & ~ENABLE);
}

static void send(uint8_t val, uint8_t mode)
{
    uint8_t high = (val & 0xF0) | mode;
    uint8_t low = ((val << 4) & 0xF0) | mode;
    pulse(high);
    pulse(low);
}

static void cmd(uint8_t val)
{
    send(val, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
}

static void data(uint8_t val)
{
    send(val, RS);
}

void lcd_init(void)
{
    i2c_config_t cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };

    i2c_param_config(I2C_NUM, &cfg);
    i2c_driver_install(I2C_NUM, cfg.mode, 0, 0, 0);

    vTaskDelay(pdMS_TO_TICKS(50));

    cmd(0x28);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x01);
}

void lcd_show_status(int temp, int hum, const char *status)
{
    char buf[17];
    cmd(0x01);

    snprintf(buf, 16, "T:%dC H:%d%%", temp, hum);
    for (int i = 0; buf[i]; i++) data(buf[i]);

    cmd(0xC0);
    for (int i = 0; status[i]; i++) data(status[i]);
}
