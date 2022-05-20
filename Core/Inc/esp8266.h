#ifndef ESP8266_H
#define ESP8266_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stm32f7xx_hal.h>
#include "http_parser.h"

#define ESP_BUFFER_SIZE 512

void esp_init(UART_HandleTypeDef* huart);

// Answers of AT commands
typedef enum {
	OK_RESPONSE,
	ERROR_RESPONSE
} BASE_RESPONSE;

#ifndef BASE_CASES
static char* BASE_CASES[] = {"OK\r\n", "ERROR\r\n"};
#endif
// End

// Modes and function AT+CWMODE
typedef enum {
	STATION_MODE,
	SOFT_AP_MODE,
	BOTH_MODE
} WIFI_MODE;

BASE_RESPONSE esp_set_wifi_mode(WIFI_MODE mode);
//

// Structure and functions AT+CIPSTA
typedef struct {
	char ip[16];
	char gateway[16];
	char netmask[16];
} NET_STATS;

BASE_RESPONSE esp_get_station_netstats(NET_STATS* stats);
BASE_RESPONSE esp_set_ip(NET_STATS config);
// End

BASE_RESPONSE esp_test();
BASE_RESPONSE esp_connect_to_wifi(char* ssid, char* pswd);

// TCP/UDP functions
typedef enum {
	AS_CLIENT_STATUS,
	AS_SERVER_STATUS,
	GOT_IP_STATUS,
	CONNECTED_STATUS,
	DISCONNECTED_STATUS
} CONNECTION_STATUS;

CONNECTION_STATUS esp_connection_status();
BASE_RESPONSE esp_create_connection(char type[], char ip[], char port[]);
BASE_RESPONSE esp_close_connection();
BASE_RESPONSE esp_send_data(char data[], size_t size);
BASE_RESPONSE esp_get_data(char data[], size_t size, uint32_t timeout);

BASE_RESPONSE esp_send_message(char ip[], char port[], char message[], char data[], size_t size);
void esp_send_request(char request[], char response[], size_t size);
char* esp_get_http_json(char request[], char buffer[], size_t size);
// End

#endif
