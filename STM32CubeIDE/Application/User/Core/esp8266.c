#include "esp8266.h"
#include "uart_ring.h"
#include <malloc.h>

char buffer[ESP_BUFFER_SIZE];


/*****************************************************************************************************************************************/

void esp_init(UART_HandleTypeDef* huart)
{
	ringbuf_init(huart);
	esp_reset();
}


BASE_RESPONSE esp_test()
{
	/********* AT **********/
	int result = -1;

	uart_send_string("AT\r\n");
	result = uart_wait_for(BASE_CASES, 2, 0);


	uart_flush();
	return result;
}


void esp_reset()
{
	/********* AT+RST **********/
	uart_send_string("AT+RST\r\n");
	osDelay(3000);

	uart_flush();

	if(esp_test() == OK_RESPONSE)
		return;
}


BASE_RESPONSE esp_set_wifi_mode(WIFI_MODE mode)
{
	/********* AT+CWMODE=<mode> **********/
	int result = -1;

	sprintf(buffer, "AT+CWMODE=%u\r\n", mode+1); // starts from 1
	uart_send_string(buffer);

	result = uart_wait_for(BASE_CASES, 2, 0);

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


BASE_RESPONSE esp_get_station_netstats(NET_STATS* stats)
{
	/********* AT+CIPSTA_CUR? **********/

	uart_send_string("AT+CIPSTA_CUR?\r\n");

	int result = -1;
	size_t buffer_size;
	result = uart_wait_until(buffer, &buffer_size, BASE_CASES, 2, 0);

	if(result == OK_RESPONSE)
	{
		memset(stats->ip, 0, 16);
		get_string_between(buffer, "CIPSTA_CUR:ip:\"", "\"\r\n+CIPSTA_CUR:gateway:", stats->ip, 0);
		memset(stats->gateway, 0, 16);
		get_string_between(buffer, "+CIPSTA_CUR:gateway:\"", "\"\r\n+CIPSTA_CUR:netmask:", stats->gateway, 0);
		memset(stats->netmask, 0, 16);
		get_string_between(buffer, "+CIPSTA_CUR:netmask:\"", "\"\r\n\r\nOK", stats->netmask, 0);
	}

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


BASE_RESPONSE esp_set_ip(NET_STATS config)
{
	/********* AT+CIPSTA=<mode> **********/
	int result = -1;

	sprintf(buffer, "AT+CIPSTA_CUR=\"%s\",\"%s\",\"\%s\"\r\n", config.ip, config.gateway, config.netmask);
	uart_send_string(buffer);

	result = uart_wait_for(BASE_CASES, 2, 0);

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


BASE_RESPONSE esp_connect_to_wifi(char* ssid, char* pswd)
{
	/********* AT+CWJAP=<ip>,<password> **********/
	int result = -1;

	sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pswd);
	uart_send_string(buffer);

	result = uart_wait_for(BASE_CASES, 2, 0);

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


CONNECTION_STATUS esp_connection_status()
{
	/********* AT+CIPSTATUS **********/

	uart_send_string("AT+CIPSTATUS\r\n");

	int result = -1;
	size_t buffer_size;
	result = uart_wait_until(buffer, &buffer_size, BASE_CASES, 2, 0);

	if(result == OK_RESPONSE)
	{
		char status[1];
		result = get_string_between(buffer, "STATUS:", "\r\n+CIPSTATUS:", status, 0);
		if(result == -1)
		{
			if(get_string_between(buffer, "STATUS:", "\r\n\r\nOK", status, 0))
				result = atoi(status);
			else
				result = DISCONNECTED_STATUS;
		}
		else
			result = atoi(status);
	}

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


BASE_RESPONSE esp_create_connection(char type[], char ip[], char port[])
{
	/********* AT+CIPSTART=<type>,<ip>,<port> **********/

	int result = -1;

	sprintf(buffer, "AT+CIPSTART=\"%s\",\"%s\",%s\r\n", type, ip, port);
	uart_send_string(buffer);

	result = uart_wait_for(BASE_CASES, 2, 0);

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


BASE_RESPONSE esp_close_connection()
{
	/********* AT+CIPCLOSE **********/

	int result = -1;

	sprintf(buffer, "AT+CIPCLOSE\r\n");
	uart_send_string(buffer);

	result = uart_wait_for(BASE_CASES, 2, 0);

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


BASE_RESPONSE esp_send_data(char data[], size_t size)
{
	/********* AT+CIPSEND= **********/

	int result = -1;

	sprintf(buffer, "AT+CIPSEND=%u\r\n", size);
	uart_send_string(buffer);

	char* cases[] = {">"};
	result = uart_wait_for(cases, 1, 1000);

	if(result == 0)
	{
		uart_send_string(data); // Data

		result = -1;
		while(result < 0)
			result = uart_wait_for(BASE_CASES, 2, 0);
	}

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return result;
}


// SLOW
BASE_RESPONSE esp_get_data(char data[], size_t size, uint32_t timeout)
{
	size_t real_size = 0;
	size_t new_size;
	int result;

	char* cases0[] = {"+IPD,", "ERROR"};
	char* cases1[] = {":"};
	do
	{
		result = uart_wait_until(buffer, &new_size, cases0, 2, timeout);
		if(result == 0)
		{
			result = uart_wait_until(buffer, &new_size, cases1, 1, 0);

			if(result == 0)
			{
				buffer[new_size-1] = '\0';
				new_size = atoi(buffer);

				if(uart_get_string(data + real_size, new_size, 0) == 0)
					real_size += new_size;
				else
					return ERROR_RESPONSE;
			}
			else
				break;
		}
	} while(result == 0);
	data[real_size] = '\0';

	uart_flush();
	memset(buffer, 0, ESP_BUFFER_SIZE);
	return (real_size > 0) ? OK_RESPONSE : ERROR_RESPONSE;
}


//// FAST
//BASE_RESPONSE esp_get_data(char* data, size_t size)
//{
//	size_t real_size = 0;
//	size_t new_size;
//	int result;
//
//	memset(data, 0, size);
//
//	char* cases[] = {"+IPD,", "CLOSED"};
//	result = uart_wait_for(cases, 2, 0);
//	if(result == 0)
//	{
//		while(1)
//		{
//			result = uart_wait_until(buffer, &new_size, cases, 2, 5000);
//
//			if(new_size + real_size > size)
//			{
//				data[0] = '\0';
//				uart_flush();
//				memset(buffer, 0, ESP_BUFFER_SIZE);
//				return ERROR_RESPONSE;
//			}
//
//			for(size_t i = 0; i < new_size; i++)
//				data[i + real_size] = buffer[i];
//			real_size += new_size;
//			memset(buffer, 0, ESP_BUFFER_SIZE);
//
//			if(result == 1 || result < 0)
//				break;
//		}
//	}
//	data[real_size] = '\0';
//
//	uart_flush();
//	return (real_size > 0) ? OK_RESPONSE : ERROR_RESPONSE;
//}


BASE_RESPONSE esp_send_message(char ip[], char port[], char message[], char data[], size_t size)
{
	uint8_t result;
	memset(data, 0, size);

	result = esp_connection_status();
	if(result != CONNECTED_STATUS)
		result = esp_create_connection("TCP", ip, port);
	else if(result == DISCONNECTED_STATUS)
	{
		result = esp_close_connection();
		result = esp_create_connection("TCP", ip, port);
	}
	else
	{
		printf("Can\'t create connection!\r\n");
		return ERROR_RESPONSE;
	}

	if(result == OK_RESPONSE)
	{
		printf("Connected to server!\r\n");

		if(esp_send_data(message, strlen(message)) == OK_RESPONSE)
		{
			if(size)
			{
				result = esp_get_data(data, size, 5000);
				if(result == OK_RESPONSE)
				{
					if(esp_connection_status() == CONNECTED_STATUS)
						esp_close_connection();
					return OK_RESPONSE;
				}
				else
					return ERROR_RESPONSE;
			}
		}
	}

	return OK_RESPONSE;
}


void esp_send_request(char request[], char response[], size_t size)
{
	http_request_t req;
	char new_request[size+1];
	strcpy(new_request, request);

	httpParseRequest(new_request, &req);

	headers_kv_t* host = httpFindHeader(req.headers, req.num_headers, "Host");

	char* spliter = strchr(host->value, (int)':');
	char* ip = host->value;
	*spliter = '\0';
	char* port = spliter + 1;

	esp_send_message(ip, port, request, response, size);

	return;
}


char* esp_get_http_json(char request[], char buffer[], size_t size)
{
	http_request_t req;
	http_response_t res;
	char new_request[size];
	strcpy(new_request, request);

	httpParseRequest(new_request, &req);

	headers_kv_t* host = httpFindHeader(req.headers, req.num_headers, "Host");

	char* spliter = strchr(host->value, (int)':');
	char* ip = host->value;
	*spliter = '\0';
	char* port = spliter + 1;

	esp_send_message(ip, port, request, buffer, size);

	char new_response[size];
	strcpy(new_response, buffer);
	httpParseResponse(new_response, &res);

	char* json = httpGetResponseBody(&res);

	// Strip
	size_t index = strlen(json) - 1; //
	for(size_t i = index; i >= 0; i--)
	{
		if(json[i] != '\r' && json[i] != '\n')
		{
			index = i + 1;
			break;
		}
	}
	json[index] = '\0';

	index = strlen(json) - 1;
	for(size_t i = 0; i < index; i++)
	{
		if(json[i] != '\r' && json[i] != '\n')
		{
			index = i;
			break;
		}
	}
	json+=index;

	return json;
}
