#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern UART_HandleTypeDef huart7;

Model::Model() : modelListener(0)
{
}

void Model::tick()
{

}

void Model::connectionInit()
{
	printf("Init WIFI!\r\n");
	esp_init(&huart7);

	char ssid[] = "IoT_Case";
	char password[] = "qweqweqwe";

	esp_set_wifi_mode(STATION_MODE);
	esp_connect_to_wifi(ssid, password);
	printf("Connected to %s\r\n", ssid);

	NET_STATS config = { "192.168.2.250", "192.168.2.1", "255.255.255.0" };
	if (esp_set_ip(config) == OK_RESPONSE)
	{
		NET_STATS stats;

		if (esp_get_station_netstats(&stats) == OK_RESPONSE)
			printf("IP: %s\r\n", stats.ip);
		else
			printf("Cannot set the IP %s\r\n", config.ip);

	}

	// "GET / HTTP/1.1\r\nHost: 192.168.0.102:80\r\n\r\n";
	char request[1024];
	sprintf(request, "GET /projects/led_controller/led HTTP/1.1\r\nHost: ridramecraft.ru:80\r\n\r\n");
	char response[8128];
	printf("JSON:\r\n%s\r\n", esp_get_http_json(request, response, 8128));

	//char json[] = "{\"color\": \"#ffffff\"}";
	//sprintf(request, "PUT /projects/led_controller/led HTTP/1.1\r\nHost: ridramecraft.ru:80\r\nContent-Type: application/json\r\nContent-Length: %u\r\n\r\n%s\r\n", strlen(json), json);
	//esp_send_request(request, response, 8128);
	//printf("Response:\r\n%s\r\n", response);
}
