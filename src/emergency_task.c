#include "tasks_common.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void emergency_task(void *pv)
{
    while (1) {
        xEventGroupWaitBits(
            fire_event_group,
            EVT_FIRE_RISK,
            pdTRUE,
            pdFALSE,
            portMAX_DELAY
        );

        gpio_set_level(LED_RED_GPIO, 1);
        gpio_set_level(BUZZER_GPIO, 1);

        vTaskDelay(pdMS_TO_TICKS(2000));

        gpio_set_level(LED_RED_GPIO, 0);
        gpio_set_level(BUZZER_GPIO, 0);
    }
}
