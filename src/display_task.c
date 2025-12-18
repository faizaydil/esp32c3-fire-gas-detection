#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "freertos/semphr.h"
#include "lcd1602_driver.h"
#include "tasks_common.h"

extern MessageBufferHandle_t sensor_msg_buffer;
extern SemaphoreHandle_t lcd_mutex;

void display_task(void *pv)
{
    dht_data_t data;
    char line[16];

    while (1) {
        if (xMessageBufferReceive(sensor_msg_buffer, &data, sizeof(data), portMAX_DELAY)) {
            if (xSemaphoreTake(lcd_mutex, portMAX_DELAY)) {
                lcd_clear();
                snprintf(line, 16, "Temp: %.1fC", data.temperature);
                lcd_print(0, 0, line);
                snprintf(line, 16, "Hum: %.1f%%", data.humidity);
                lcd_print(1, 0, line);
                xSemaphoreGive(lcd_mutex);
            }
        }
    }
}
