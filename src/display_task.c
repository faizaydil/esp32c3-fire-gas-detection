#include "tasks_common.h"
#include "freertos/task.h"
#include "lcd1602_driver.h"

void display_task(void *pv)
{
    dht_data_t data;

    while (1) {
        if (xMessageBufferReceive(sensor_msg_buffer, &data, sizeof(data), 0)) {

            if (xSemaphoreTake(lcd_mutex, portMAX_DELAY)) {

                if (data.temperature > TEMP_THRESHOLD &&
                    data.humidity < HUM_THRESHOLD) {
                    lcd_show_status(data.temperature, data.humidity, "FIRE RISK");
                    gpio_set_level(LED_GREEN_GPIO, 0);
                } else {
                    lcd_show_status(data.temperature, data.humidity, "NORMAL");
                    gpio_set_level(LED_GREEN_GPIO, 1);
                }

                xSemaphoreGive(lcd_mutex);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
