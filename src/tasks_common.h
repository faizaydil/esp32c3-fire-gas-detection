#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/message_buffer.h"
#include "freertos/semphr.h"

/* ================= GPIO ================= */
#define DHT11_GPIO        4
#define BUZZER_GPIO       8

/* ================= EVENT BITS ============ */
#define EVT_FIRE_RISK     (1 << 0)

/* ================= DATA STRUCT =========== */
typedef struct {
    double temperature;
    double humidity;
} dht_data_t;

/* ================= SHARED RTOS OBJECTS ==== */
extern EventGroupHandle_t fire_event_group;
extern MessageBufferHandle_t sensor_msg_buffer;
extern SemaphoreHandle_t lcd_mutex;
