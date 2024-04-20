#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "gh_common_freertos.h"


#define BLINK_GPIO 2
#define BUILT_IN_LED "BUILT_IN_LED"
/**
 * @brief wow here we have got a simple solution to configure a GPIO an an OUTPUT
*/
void configure_led(void);

void vLED_TaskCode(void * pvParameters);