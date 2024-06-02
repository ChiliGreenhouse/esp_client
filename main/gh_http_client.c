#include "gh_http_client.h"

static esp_err_t client_event_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}

void gh_url_get_test(uint8_t * url) {
    esp_http_client_config_t config_post = {
        .url = (const char *) url,
        .method = HTTP_METHOD_GET,
        .cert_pem = NULL,
        .event_handler = client_event_handler};

    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}

void gh_post_data(uint8_t* url, uint8_t* data) {
    esp_http_client_config_t config_post = {
        .url = (const char *) url,
        .method = HTTP_METHOD_POST,
        .cert_pem = NULL,
        .event_handler = client_event_handler};

    esp_http_client_handle_t client = esp_http_client_init(&config_post);
    
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, (const char *) data, strlen((const char*) data));

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}
