#include "tasks_common.h"
#include "oled_driver.h"

static const char *TAG = "DISPLAY_TASK";

void task_display(void *pv) {
    SensorMsg_t rx;
    char buf[32];

    while (1) {
        size_t r = xMessageBufferReceive(xSensorMsgBuf, &rx, sizeof(rx), pdMS_TO_TICKS(2000));
        if (r != sizeof(rx)) continue;

        if (xSemaphoreTake(xResourceMutex, pdMS_TO_TICKS(1000))) {
            oled_clear();
            sprintf(buf, "MQ2: %s", rx.mq2_do ? "ALARM" : "OK");
            oled_draw_text(0, 0, buf);

            sprintf(buf, "MQ135: %s", rx.mq135_do ? "ALARM" : "OK");
            oled_draw_text(0, 12, buf);

            oled_update();
            xSemaphoreGive(xResourceMutex);
        }
    }
}
