#include "lcd1602_driver.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_SDA GPIO_NUM_9
#define I2C_SCL GPIO_NUM_10
#define LCD_ADDR 0x27

static i2c_master_bus_handle_t bus;
static i2c_master_dev_handle_t dev;

static void lcd_write(uint8_t data)
{
    i2c_master_transmit(dev, &data, 1, -1);
}

void lcd_init(void)
{
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = 0,
        .sda_io_num = I2C_SDA,
        .scl_io_num = I2C_SCL,
        .flags.enable_internal_pullup = true,
    };

    i2c_new_master_bus(&bus_cfg, &bus);

    i2c_device_config_t dev_cfg = {
        .device_address = LCD_ADDR,
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .scl_speed_hz = 100000,
    };

    i2c_master_bus_add_device(bus, &dev_cfg, &dev);
    vTaskDelay(pdMS_TO_TICKS(50));
    lcd_clear();
}

void lcd_clear(void)
{
    lcd_write(0x01);
    vTaskDelay(pdMS_TO_TICKS(5));
}

void lcd_set_cursor(int col, int row)
{
    lcd_write((row == 0 ? 0x80 : 0xC0) + col);
}

void lcd_print(const char *str)
{
    while (*str)
        lcd_write(*str++);
}
