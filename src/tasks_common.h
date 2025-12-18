#pragma once
#include "driver/gpio.h"

/* GPIO pins */
#define DHT11_GPIO        GPIO_NUM_4
#define LED_RED_GPIO      GPIO_NUM_5
#define LED_GREEN_GPIO    GPIO_NUM_6
#define LED_YELLOW_GPIO   GPIO_NUM_7
#define BUZZER_GPIO       GPIO_NUM_8

/* Event bits */
#define TEMP_EVENT_BIT    (1 << 0)

/* Sensor data */
typedef struct {
    float temperature;
    float humidity;
} dht_data_t;
