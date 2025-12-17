#include "tasks_common.h"
#include "freertos/task.h"

void monitor_task(void *pv)
{
    dht_data_t data;

    while (1) {
        if (xMessageBufferReceive(sensor_msg_buffer, &data, sizeof(data), portMAX_DELAY)) {
            if (data.temperature > TEMP_THRESHOLD &&
                data.humidity < HUM_THRESHOLD) {
                xEventGroupSetBits(fire_event_group, EVT_FIRE_RISK);
            }
        }
    }
}
