#ifndef TASKS_COMMON_H
#define TASKS_COMMON_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"

// ---- GPIO MAP ----
#define MQ2_DO_GPIO        GPIO_NUM_6
#define MQ135_DO_GPIO      GPIO_NUM_7
#define BUZZER_GPIO        GPIO_NUM_5
#define LED_RED_GPIO       GPIO_NUM_3
#define LED_GREEN_GPIO     GPIO_NUM_4
#define LED_YELLOW_GPIO    GPIO_NUM_2
#define OLED_SDA_GPIO      GPIO_NUM_9
#define OLED_SCL_GPIO      GPIO_NUM_10

// Message buffer size
#define MSG_BUF_SIZE       128

// Event bits
#define BIT_MQ2_ALARM      (1 << 0)
#define BIT_MQ135_ALARM    (1 << 1)

// Struct for sensor data
typedef struct {
    uint32_t ts;
    bool mq2_do;
    bool mq135_do;
} SensorMsg_t;

// Global handles
extern MessageBufferHandle_t xSensorMsgBuf;
extern EventGroupHandle_t xEventGroup;
extern SemaphoreHandle_t xResourceMutex;
extern TaskHandle_t xEmergencyTaskHandle;

#endif
