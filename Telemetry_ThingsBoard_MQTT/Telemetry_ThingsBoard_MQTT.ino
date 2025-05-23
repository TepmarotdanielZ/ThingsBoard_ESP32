
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "DREAMSLAB UNIFI";
const char* password = "@DREAMSLAB2023";

// ThingsBoard server and device access token
const char* mqtt_server = "demo.thingsboard.io";
const int mqtt_port = 1883;
const char* access_token = "cNBxUhUuKHzzt734YUuL"; 

// MQTT topic for telemetry
const char* telemetry_topic = "v1/devices/me/telemetry";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublish = 0;
const unsigned long publishInterval = 10000; // 10 seconds

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", access_token, NULL)) {
      Serial.println("connected to ThingsBoard");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastPublish >= publishInterval) {
    lastPublish = now;

    const char* payload = "{\"temperature1\":250}";
    Serial.print("Publishing payload: ");
    Serial.println(payload);

    if (client.publish(telemetry_topic, payload)) {
      Serial.println("Telemetry published successfully.");
    } else {
      Serial.println("Telemetry publish failed!");
    }
  }
}



