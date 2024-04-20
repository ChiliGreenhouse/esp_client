/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#include "sdkconfig.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"
#include "driver/gpio.h"

#include "time.h"
#include "sys/time.h"

#include "gh_bt.h"
#include "gh_wifi.h"
//#include "gh_gpio_config.h" 
#include "gh_common_freertos.h"

EventGroupHandle_t xLED_EventGroup;
QueueHandle_t xBT_Queue;


void app_main(void)
{
    /*configure_led();
    xLED_EventGroup = xEventGroupCreate();
    ESP_LOGI(BUILT_IN_LED, "xLED_EventGroup created: %s", (xLED_EventGroup==NULL) ? "N" : "Y");

    TaskHandle_t xTaskHandleLED = NULL;
    xTaskCreate(vLED_TaskCode,
                "Cool LED",
                2*configMINIMAL_STACK_SIZE,
                NULL,
                10,
                &xTaskHandleLED);
    ESP_LOGI(BUILT_IN_LED, "Cool LED Task  created: %s", (xTaskHandleLED==NULL) ? "N" : "Y");*/         

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ret = gh_bt_start_srv();
    ESP_ERROR_CHECK( ret );

    xBT_Queue = xQueueCreate(4 , sizeof(gh_bt_data));
    ESP_LOGI(GH_DEVICE_NAME, "xBT_Queue created: %s", (xBT_Queue==NULL) ? "N" : "Y");

    TaskHandle_t xTaskHandleBtDecode = NULL;
    xTaskCreate(vBT_decoder,
                BT_DECODE,
                2*configMINIMAL_STACK_SIZE,
                NULL,
                10,     
                &xTaskHandleBtDecode);
    ESP_LOGI(BT_DECODE, "BT_decoder  created: %s", (xTaskHandleBtDecode==NULL) ? "N" : "Y"); 

    gh_wifi_init_sta();

    }
