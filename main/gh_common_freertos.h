#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"

#define BUILT_IN_LED_ON 0x1 << 0
#define BUILT_IN_LED_OFF 0x1 << 1

extern EventGroupHandle_t xLED_EventGroup;

extern QueueHandle_t xBT_Queue;

extern QueueHandle_t xPostSensorDataQueue;
