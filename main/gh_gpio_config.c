#include "gh_gpio_config.h"

/**
 * @brief wow here we have got a simple solution to configure a GPIO an an OUTPUT
*/
void configure_led(void)
{
    ESP_LOGI(BUILT_IN_LED, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void vLED_TaskCode(void * pvParameters)
{
    EventBits_t uxBits;
    for( ;; )
    {
        uxBits = xEventGroupWaitBits(xLED_EventGroup,
                                     BUILT_IN_LED_ON | BUILT_IN_LED_OFF,
                                     pdTRUE,
                                     pdFALSE,
                                     portMAX_DELAY 
                                    );
        ESP_LOGI(BUILT_IN_LED, "Wow, I got called!!!");
        switch (uxBits)
        {
        case BUILT_IN_LED_ON:
            gpio_set_level(BLINK_GPIO, 1);
            ESP_LOGI(BUILT_IN_LED, "Let there be light");
            break;
        case BUILT_IN_LED_OFF:
            gpio_set_level(BLINK_GPIO, 0);
            ESP_LOGI(BUILT_IN_LED, "Let there NOT be light");
            break;
        default:
            break;
        }       
    }
    vTaskDelete(NULL);
}