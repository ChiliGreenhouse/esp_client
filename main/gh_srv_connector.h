#pragma once

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#include "gh_common_freertos.h"
#include "gh_devices.h"
#include "gh_http_client.h"

#define GH_SRV_CONNECTOR "GH_SRV_CONNECTOR"

typedef struct gh_post_data_t{
    uint8_t* sensor_name;
    float data;
} gh_post_data_t;

void vSRV_connector(void * pvURL);