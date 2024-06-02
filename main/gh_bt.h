#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

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
#include "gh_common_freertos.h"
#include "gh_wifi.h"
#include "gh_http_client.h"
#include "gh_srv_connector.h"

#define SPP_TAG "SPP_ACCEPTOR_DEMO"
#define SPP_SERVER_NAME "SPP_SERVER"
#define GH_DEVICE_NAME "GH"
#define BT_DECODE "BT_DECODE"


static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;
static const bool esp_spp_enable_l2cap_ertm = true;


static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;

typedef struct gh_bt_data
{
    uint16_t            len;            /*!< The length of data */
    uint8_t             data[128];          /*!< The data received */
}gh_bt_data;


char *bda2str(uint8_t * bda, char *str, size_t size);

void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);

void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

esp_err_t gh_bt_start_srv(void);

void vBT_decoder(void * pvParameters);
