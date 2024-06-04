#pragma once

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "gh_common_freertos.h"

#include "gh_srv_connector.h"

#define GH_TEMP_DEVICE "GH_TEMP_DEVICE"

#define GH_SOIL_DEVICE "GH_SOIL_DEVICE"

#define TEMP_ADC1_CHANEL ADC_CHANNEL_4
#define SOIL_ADC1_CHANEL ADC_CHANNEL_5

// Constants for the MF52d thermistor
#define NOMINAL_RESISTANCE 100000.0  // Nominal resistance at 25°C (in ohms)
#define NOMINAL_TEMPERATURE 20.0     // Temperature for nominal resistance (in °C)
#define B_VALUE 4050.0               // B-value or beta coefficient of the thermistor

// Supply voltage (in volts)
#define SUPPLY_VOLTAGE 3.3


void vTemp_sense(void * pvDevName);

void vSoil_sense(void * pvDevName);

void init_adc();

float adc_to_temperature(int adc_value);
