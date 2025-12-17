#include "tasks_common.h"
#include "freertos/task.h"

/* Dummy DHT11 Read (Replace with real driver if needed) */
static void read_dht11(dht_data_t *data)
{
    data->temperature = 25 + (esp_random() % 15);
    data->humidity = 40 + (esp_random() % 30);
}

void dht11_task(void *pv)
{
    dht_data_t data;

    while (1) {
        read_dht11(&data);
        xMessageBufferSend(sensor_msg_buffer, &data, sizeof(data), 0);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
