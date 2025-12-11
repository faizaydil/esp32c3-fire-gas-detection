#include "tasks_common.h"

static const char *TAG = "CLOUD_TASK";

void task_cloud(void *pv) {

    // TODO: RainMaker Init
    // TODO: Register parameters:
    // - mq2_status
    // - mq135_status
    // - alarm_enable
    // - sensitivity
    // TODO: Push notifications when alarm triggers

    while (1) {
        ESP_LOGI(TAG, "Cloud heartbeat...");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
