#include "tasks_common.h"

static const char *TAG = "MONITOR_TASK";

void task_monitor(void *pv) {
    SensorMsg_t rx;

    while (1) {
        size_t r = xMessageBufferReceive(xSensorMsgBuf, &rx, sizeof(rx), portMAX_DELAY);
        if (r != sizeof(rx)) continue;

        EventBits_t bits = 0;

        if (rx.mq2_do) bits |= BIT_MQ2_ALARM;
        if (rx.mq135_do) bits |= BIT_MQ135_ALARM;

        if (bits) {
            xEventGroupSetBits(xEventGroup, bits);
            xTaskNotifyGive(xEmergencyTaskHandle);
        }
    }
}
