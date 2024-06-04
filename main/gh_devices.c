#include "gh_devices.h"

static adc_oneshot_unit_handle_t adc_handle = {0};
static adc_oneshot_chan_cfg_t config;

void vTemp_sense(void * pvDevName) {
    uint8_t name[32] = {0};
    int raw_temp = 0;
    float temp = 0.0;
    memcpy(name, pvDevName, strlen((const char *)pvDevName));

    gh_post_data_t data  = { 
        .sensor_name = name,
        .data = 0
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, TEMP_ADC1_CHANEL, &config));

    for(;;) {

        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, TEMP_ADC1_CHANEL, &raw_temp));
        ESP_LOGI(GH_TEMP_DEVICE, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, TEMP_ADC1_CHANEL, raw_temp);
        temp = adc_to_temperature(raw_temp);
        ESP_LOGI(GH_TEMP_DEVICE, "ADC%d Channel[%d] Temp Data: %f °C", ADC_UNIT_1 + 1, TEMP_ADC1_CHANEL, temp);
        data.data = temp;

        xQueueSend( xPostSensorDataQueue,
                    ( void * ) &data,
                    ( TickType_t ) 10 );

        vTaskDelay(( TickType_t ) 500);
    }
    vTaskDelete(NULL);
}


void vSoil_sense(void * pvDevName) {
    uint8_t name[32] = {0};
    int raw_soil = 0;
    float soil = 0.0;
    memcpy(name, pvDevName, strlen((const char *)pvDevName));

    gh_post_data_t data  = { 
        .sensor_name = name,
        .data = 0
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, SOIL_ADC1_CHANEL, &config));

    for(;;) {

        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, SOIL_ADC1_CHANEL, &raw_soil));
        ESP_LOGI(GH_SOIL_DEVICE, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, SOIL_ADC1_CHANEL, raw_soil);
        soil = ((float)(4095-raw_soil)/4095.0) * 100; 
        ESP_LOGI(GH_SOIL_DEVICE, "ADC%d Channel[%d] Soil Data: %f%%", ADC_UNIT_1 + 1, SOIL_ADC1_CHANEL, soil);
        data.data = soil;

        xQueueSend( xPostSensorDataQueue,
                    ( void * ) &data,
                    ( TickType_t ) 10 );

        vTaskDelay(( TickType_t ) 500);
    }
    vTaskDelete(NULL);
}

void init_adc() {
    adc_oneshot_unit_init_cfg_t init = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init, &adc_handle));

    config.bitwidth = ADC_BITWIDTH_DEFAULT;
    config.atten = ADC_ATTEN_DB_11;
}

float adc_to_temperature(int adc_value) {
    float resistance, temperature;
    float voltage = (float)adc_value * SUPPLY_VOLTAGE / 4095.0;  // Calculate voltage across thermistor

    // Calculate resistance of the thermistor
    //resistance = NOMINAL_RESISTANCE * SUPPLY_VOLTAGE / voltage - NOMINAL_RESISTANCE;

    resistance = voltage / ((SUPPLY_VOLTAGE-voltage) / NOMINAL_RESISTANCE);

    // Calculate temperature using the B-value equation
    temperature = 1.0 / (1.0 / (NOMINAL_TEMPERATURE + 273.15) + (1.0 / B_VALUE) * log(resistance / NOMINAL_RESISTANCE)) - 273.15;

    return temperature;
}