#include "tasks_common.h"
#include "oled_driver.h"

MessageBufferHandle_t xSensorMsgBuf = NULL;
EventGroupHandle_t xEventGroup = NULL;
SemaphoreHandle_t xResourceMutex = NULL;
TaskHandle_t xEmergencyTaskHandle = NULL;

extern void task_sensor(void*);
extern void task_monitor(void*);
extern void task_emergency(void*);
extern void task_display(void*);
extern void task_cloud(void*);

// ISR handler
static void IRAM_ATTR mq_isr(void *arg) {
    uint32_t pin = (uint32_t)arg;

    if (pin == MQ2_DO_GPIO) {
        xEventGroupSetBitsFromISR(xEventGroup, BIT_MQ2_ALARM, NULL);
    }
    if (pin == MQ135_DO_GPIO) {
        xEventGroupSetBitsFromISR(xEventGroup, BIT_MQ135_ALARM, NULL);
    }

    vTaskNotifyGiveFromISR(xEmergencyTaskHandle, NULL);
}

static void gpio_init(void) {

    gpio_config_t outcfg = {
        .pin_bit_mask = ((1ULL << BUZZER_GPIO) |
                         (1ULL << LED_RED_GPIO) |
                         (1ULL << LED_GREEN_GPIO) |
                         (1ULL << LED_YELLOW_GPIO)),
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&outcfg);

    gpio_set_level(LED_GREEN_GPIO, 1);

    gpio_config_t incfg = {
        .pin_bit_mask = ((1ULL << MQ2_DO_GPIO) | (1ULL << MQ135_DO_GPIO)),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = true,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&incfg);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(MQ2_DO_GPIO, mq_isr, (void*)MQ2_DO_GPIO);
    gpio_isr_handler_add(MQ135_DO_GPIO, mq_isr, (void*)MQ135_DO_GPIO);
}

void app_main(void) {

    gpio_init();
    oled_init();

    xSensorMsgBuf = xMessageBufferCreate(MSG_BUF_SIZE);
    xEventGroup = xEventGroupCreate();
    xResourceMutex = xSemaphoreCreateMutex();

    xTaskCreate(task_sensor, "T_SENSOR", 4096, NULL, 2, NULL);
    xTaskCreate(task_monitor, "T_MONITOR", 4096, NULL, 3, NULL);
    xTaskCreate(task_emergency, "T_EMERG", 4096, NULL, 4, &xEmergencyTaskHandle);
    xTaskCreate(task_display, "T_DISPLAY", 4096, NULL, 2, NULL);
    xTaskCreate(task_cloud, "T_CLOUD", 4096, NULL, 2, NULL);
}
