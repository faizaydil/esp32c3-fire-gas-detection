#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "tasks_common.h"

extern MessageBufferHandle_t sensor_msg_buffer;

void dht11_task(void *pv)
{
    dht_data_t data;

    while (1) {
        data.temperature = 35.0;   // simulated
        data.humidity = 60.0;

        xMessageBufferSend(sensor_msg_buffer, &data, sizeof(data), 0);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
