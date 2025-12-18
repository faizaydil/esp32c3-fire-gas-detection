#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"

#include "tasks_common.h"
#include "lcd1602_driver.h"

extern MessageBufferHandle_t sensor_msg_buffer;
extern EventGroupHandle_t fire_event_group;
extern SemaphoreHandle_t lcd_mutex;

void display_task(void *pv)
{
    dht_data_t data;
    char line1[17];
    char line2[17];

    while (1) {
        if (xMessageBufferReceive(sensor_msg_buffer,
                                  &data,
                                  sizeof(data),
                                  portMAX_DELAY) == sizeof(data)) {

            if (xSemaphoreTake(lcd_mutex, portMAX_DELAY)) {

                snprintf(line1, 17, "T:%.1fC H:%.1f%%",
                         data.temperature, data.humidity);

                if (xEventGroupGetBits(fire_event_group) & EVT_FIRE_RISK)
                    snprintf(line2, 17, "!! FIRE RISK !!");
                else
                    snprintf(line2, 17, "Status: NORMAL");

                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print(line1);
                lcd_set_cursor(0, 1);
                lcd_print(line2);

                xSemaphoreGive(lcd_mutex);
            }
        }
    }
}
