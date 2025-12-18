#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/message_buffer.h"
#include "freertos/semphr.h"

#include "tasks_common.h"
#include "lcd1602_driver.h"

/* RTOS Objects */
EventGroupHandle_t fire_event_group;
MessageBufferHandle_t sensor_msg_buffer;
SemaphoreHandle_t lcd_mutex;

/* Task prototypes */
void dht11_task(void *pv);
void monitor_task(void *pv);
void emergency_task(void *pv);
void display_task(void *pv);

void app_main(void)
{
    lcd_init();

    fire_event_group = xEventGroupCreate();
    sensor_msg_buffer = xMessageBufferCreate(sizeof(dht_data_t));
    lcd_mutex = xSemaphoreCreateMutex();

    xTaskCreate(dht11_task, "DHT11", 4096, NULL, 3, NULL);
    xTaskCreate(monitor_task, "Monitor", 4096, NULL, 3, NULL);
    xTaskCreate(emergency_task, "Emergency", 4096, NULL, 4, NULL);
    xTaskCreate(display_task, "Display", 4096, NULL, 2, NULL);
}
