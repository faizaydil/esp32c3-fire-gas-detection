#include "tasks_common.h"
#include "freertos/task.h"

extern void oled_show_status(int temp, int hum, const char *status);

void display_task(void *pv)
{
    dht_data_t data;

    while (1) {
        if (xMessageBufferReceive(sensor_msg_buffer, &data, sizeof(data), 0)) {

            if (xSemaphoreTake(oled_mutex, portMAX_DELAY)) {
                if (data.temperature > TEMP_THRESHOLD && data.humidity < HUM_THRESHOLD)
                    oled_show_status(data.temperature, data.humidity, "FIRE RISK");
                else
                    oled_show_status(data.temperature, data.humidity, "NORMAL");

                xSemaphoreGive(oled_mutex);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
