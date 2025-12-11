#include "tasks_common.h"
#include "oled_driver.h"

static const char *TAG = "EMERGENCY_TASK";

void task_emergency(void *pv) {

    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        EventBits_t bits = xEventGroupGetBits(xEventGroup);

        if (bits == 0) continue;

        if (xSemaphoreTake(xResourceMutex, pdMS_TO_TICKS(2000))) {

            oled_clear();

            if (bits & BIT_MQ2_ALARM)
                oled_draw_text(0, 0, "MQ-2 GAS ALERT!");

            if (bits & BIT_MQ135_ALARM)
                oled_draw_text(0, 12, "MQ-135 AIR HAZARD!");

            oled_update();

            // LED + buzzer
            gpio_set_level(LED_RED_GPIO, 1);
            for (int i = 0; i < 3; i++) {
                gpio_set_level(BUZZER_GPIO, 1);
                vTaskDelay(pdMS_TO_TICKS(200));
                gpio_set_level(BUZZER_GPIO, 0);
                vTaskDelay(pdMS_TO_TICKS(200));
            }
            gpio_set_level(LED_RED_GPIO, 0);

            // Clear flags
            xEventGroupClearBits(xEventGroup, BIT_MQ2_ALARM | BIT_MQ135_ALARM);

            xSemaphoreGive(xResourceMutex);
        }
    }
}
