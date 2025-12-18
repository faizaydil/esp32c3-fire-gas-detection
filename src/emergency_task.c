#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "tasks_common.h"

extern EventGroupHandle_t fire_event_group;

void emergency_task(void *pv)
{
    while (1) {
        EventBits_t bits = xEventGroupWaitBits(
            fire_event_group,
            TEMP_EVENT_BIT,
            pdTRUE,
            pdFALSE,
            portMAX_DELAY
        );

        if (bits & TEMP_EVENT_BIT) {
            gpio_set_level(LED_RED_GPIO, 1);
            gpio_set_level(BUZZER_GPIO, 1);
        }
    }
}
