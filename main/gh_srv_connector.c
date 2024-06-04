#include "gh_srv_connector.h"

QueueHandle_t xPostSensorDataQueue;

void vSRV_connector(void * pvURL) {
    uint8_t url[128] = {0};
    uint8_t url_buff[256] = {0};
    uint8_t data_buff[128] = {0};
    gh_post_data_t data;

    memcpy(url, pvURL, strlen((const char *)pvURL));
    strcat((char *) url, "/api/v0/gh/0/devices");
    ESP_LOGI(GH_SRV_CONNECTOR, "I got created and received the url %s", url);

    uint8_t temp_sensor[] = "temperature";
    uint8_t moisture_sensor[] = "soil_moisture";

    xPostSensorDataQueue = xQueueCreate(5, sizeof(gh_post_data_t));
    ESP_LOGI(GH_SRV_CONNECTOR, "xPostSensorDataQueue created: %s", (xPostSensorDataQueue==NULL) ? "N" : "Y");

    init_adc();

    sprintf((char *)data_buff, "{\"name\":\"%s\",\"type\":{\"SENSOR\":{}}}", temp_sensor);
    gh_post_data(url, data_buff);

    TaskHandle_t xTaskHandleTempDevice = NULL;

    xTaskCreate(vTemp_sense,
                GH_TEMP_DEVICE,
                2*configMINIMAL_STACK_SIZE,
                temp_sensor,
                10,     
                &xTaskHandleTempDevice);

    sprintf((char *)data_buff, "{\"name\":\"%s\",\"type\":{\"SENSOR\":{}}}", moisture_sensor);
    gh_post_data(url, data_buff);

    TaskHandle_t xTaskHandleSoilDevice = NULL;

    xTaskCreate(vSoil_sense,
                GH_SOIL_DEVICE,
                2*configMINIMAL_STACK_SIZE,
                moisture_sensor,
                10,     
                &xTaskHandleSoilDevice);

    /**
     * TODO POST REST API call to create the sensor devices on the server
     * url:     url+/api/v0/gh/0/devices
     * data:    {"name":"%s","type":{"SENSOR":{}}} ,temp_sensor | moisture_sensor
     * */ 

    
    // TODO Create sensor_tasks to send data to the queue 
    for(;;) {
        xQueueReceive(  xPostSensorDataQueue,
                        &data ,
                         portMAX_DELAY);

        sprintf((char *) data_buff, "{\"value\":%f}", data.data);
        sprintf((char *) url_buff, "%s/%s/datapoints", url, data.sensor_name); 
        gh_post_data(url_buff, data_buff);

    }
    vTaskDelete(NULL);
}