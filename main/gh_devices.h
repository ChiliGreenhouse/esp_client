#pragma once

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "gh_common_freertos.h"

#include "gh_srv_connector.h"

#define GH_TEMP_DEVICE "GH_TEMP_DEVICE"

#define GH_SOIL_DEVICE "GH_SOIL_DEVICE"

void vTemp_sense(void * pvDevName);

void vSoil_sense(void * pvDevName);
