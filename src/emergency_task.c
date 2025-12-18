#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "tasks_common.h"

extern EventGroupHandle_t fire_event_group;

void emergency_task(void *pv)
{
    gpio_set_direction(BUZZER_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        xEventGroupWaitBits(
            fire_event_group,
            EVT_FIRE_RISK,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY
        );

        gpio_set_level(BUZZER_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(BUZZER_GPIO, 0);
    }
}
