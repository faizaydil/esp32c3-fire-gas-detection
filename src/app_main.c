#include "tasks_common.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/* Handles */
EventGroupHandle_t fire_event_group;
MessageBufferHandle_t sensor_msg_buffer;
SemaphoreHandle_t oled_mutex;

/* Task Prototypes */
void dht11_task(void *pv);
void monitor_task(void *pv);
void emergency_task(void *pv);
void display_task(void *pv);

void app_main(void)
{
    fire_event_group = xEventGroupCreate();
    sensor_msg_buffer = xMessageBufferCreate(sizeof(dht_data_t) * 4);
    oled_mutex = xSemaphoreCreateMutex();

    gpio_set_direction(LED_RED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEN_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_YELLOW_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUZZER_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(dht11_task, "DHT11 Task", 4096, NULL, 2, NULL);
    xTaskCreate(monitor_task, "Monitor Task", 4096, NULL, 3, NULL);
    xTaskCreate(emergency_task, "Emergency Task", 4096, NULL, 5, NULL);
    xTaskCreate(display_task, "Display Task", 4096, NULL, 1, NULL);
}
