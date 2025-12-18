#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "freertos/event_groups.h"
#include "tasks_common.h"

extern EventGroupHandle_t fire_event_group;
extern MessageBufferHandle_t sensor_msg_buffer;

void monitor_task(void *pv)
{
    dht_data_t data;

    while (1) {
        if (xMessageBufferReceive(sensor_msg_buffer,
                                  &data,
                                  sizeof(data),
                                  portMAX_DELAY) == sizeof(data)) {

            if (data.temperature > 40.0) {
                xEventGroupSetBits(fire_event_group, EVT_FIRE_RISK);
            } else {
                xEventGroupClearBits(fire_event_group, EVT_FIRE_RISK);
            }
        }
    }
}
