// #define WIFI_SSID "f18962"
// #define WIFI_PASSWORD "330928557WiFi9876"

// #define WIFI_SSID "Redmi Note 8"
// #define WIFI_PASSWORD "c6220dc1cc20"


#define WIFI_SSID "iPhone de Terrones"
#define WIFI_PASSWORD "holahola"


#define MQTT_SERVER_PORT 1883
#define MQTT_SERVER_HOST "test.mosquitto.org"
#define MQTT_TOPIC_SUSCRIBE "smart_trash/listening"
#define MQTT_TOPIC_PUBLISH "smart_trash/client"


class MQTTClient {
  public:
    void WIFI_init(void);
    void MQTT_init(void);
    void MQTT_reconnect(void);
    void publish_state_to_subscribers(void);
};


void MQTTClient::WIFI_init(void) {
	Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	while(WiFi.status() != WL_CONNECTED) {
		Serial.println("[...] Conectando a " + String(WIFI_SSID) + "...");
		delay(5000);
	}
	Serial.println(F("[Success] Red conectada!"));
	Serial.print(F("[Info] Dirección IP: "));
	Serial.println(WiFi.localIP());
  Serial.println();
}


// Inicializa el broker
void MQTTClient::MQTT_init(void) {
	mqtt.setCallback(callback);
	mqtt.setServer(MQTT_SERVER_HOST, MQTT_SERVER_PORT);	
}


// Intenta conectar al broker en caso de no estarlo
void MQTTClient::MQTT_reconnect(void) {
	while(!mqtt.connected()) {
		Serial.println(F("[...] Conectando servidor MQTT..."));
		if (mqtt.connect("esp32Client")) {
			Serial.println(F("[Success] MQTT conectado!"));
			mqtt.subscribe(MQTT_TOPIC_SUSCRIBE);
		} else {
			Serial.print(F("[Error] Fallo al conectar broker, rc="));
			Serial.print(mqtt.state());
			Serial.println(F(" (Intentando de nuevo...)"));
			delay(2000);
		}
	}
}
