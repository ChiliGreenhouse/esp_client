#include "esp_http_client.h"

static esp_err_t client_event_handler(esp_http_client_event_handle_t evt);

void gh_url_get_test(uint8_t * url);

void gh_post_data(uint8_t* url, uint8_t* data);