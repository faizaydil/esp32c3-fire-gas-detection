#include "oled_driver.h"
#include "esp_log.h"

// Replace with real SSD1306 driver later
void oled_init(void) {
    ESP_LOGI("OLED", "OLED init placeholder");
}
void oled_clear(void) {}
void oled_draw_text(int x, int y, const char *txt) {
    ESP_LOGI("OLED", "%s", txt);
}
void oled_update(void) {}
