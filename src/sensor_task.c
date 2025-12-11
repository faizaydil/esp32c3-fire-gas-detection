#include "tasks_common.h"

static const char *TAG = "SENSOR_TASK";

void task_sensor(void *pv) {
    SensorMsg_t msg;

    while (1) {
        msg.ts = esp_timer_get_time() / 1000ULL;
        msg.mq2_do = (gpio_get_level(MQ2_DO_GPIO) == 0);
        msg.mq135_do = (gpio_get_level(MQ135_DO_GPIO) == 0);

        xMessageBufferSend(xSensorMsgBuf, &msg, sizeof(msg), 0);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
