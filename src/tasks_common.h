#ifndef TASKS_COMMON_H
#define TASKS_COMMON_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/message_buffer.h"
#include "freertos/semphr.h"

/* GPIO Mapping */
#define DHT11_GPIO        8
#define LCD_SDA_GPIO      9
#define LCD_SCL_GPIO      10
#define BUZZER_GPIO       5
#define LED_RED_GPIO      3
#define LED_GREEN_GPIO    4
#define LED_YELLOW_GPIO   2

/* Fire Risk Thresholds */
#define TEMP_THRESHOLD    35
#define HUM_THRESHOLD     30

/* Event Group Bits */
#define EVT_FIRE_RISK     (1 << 0)

/* Shared RTOS Objects */
extern EventGroupHandle_t fire_event_group;
extern MessageBufferHandle_t sensor_msg_buffer;
extern SemaphoreHandle_t lcd_mutex;

/* Sensor Data Structure */
typedef struct {
    int temperature;
    int humidity;
} dht_data_t;

#endif
