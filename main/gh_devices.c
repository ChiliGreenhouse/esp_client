#include "gh_devices.h"

void vTemp_sense(void * pvDevName) {
    uint8_t name[32] = {0};
    memcpy(name, pvDevName, strlen((const char *)pvDevName));
    int i = 0;

    gh_post_data_t data  = { 
        .sensor_name = name,
        .data = 20
    };

    for(;;) {
        xQueueSend( xPostSensorDataQueue,
                    ( void * ) &data,
                    ( TickType_t ) 10 );
        
        i++;
        data.data = 20 + (i % 4);

        vTaskDelay(( TickType_t ) 500);
    }
    vTaskDelete(NULL);
}


void vSoil_sense(void * pvDevName) {
    uint8_t name[32] = {0};
    memcpy(name, pvDevName, strlen((const char *)pvDevName));
    int i = 0;

    gh_post_data_t data  = { 
        .sensor_name = name,
        .data = 39
    };

    for(;;) {
        xQueueSend( xPostSensorDataQueue,
                    ( void * ) &data,
                    ( TickType_t ) 10 );
        
        i++;
        data.data = 39 + (i % 4);

        vTaskDelay(( TickType_t ) 500);
    }
    vTaskDelete(NULL);
}