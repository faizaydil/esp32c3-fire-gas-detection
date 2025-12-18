#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tasks_common.h"

extern MessageBufferHandle_t sensor_msg_buffer;

void dht11_task(void *pv)
{
    dht_data_t data;

    while (1) {
        data.temperature = 20 + (rand() % 30);   // 20–49 °C
        data.humidity = 40 + (rand() % 40);      // 40–79 %

        xMessageBufferSend(sensor_msg_buffer, &data, sizeof(data), 0);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
