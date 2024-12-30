#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Replace with your network credentials
const char* ssid = "Neatic";
const char* password = "1234567890";

// MQTT Broker details
const char* mqttServer = "chiptree-iot.aifarm.dev";
const int mqttPort = 1883;
const char* mqttUser = "sZMJQcf5H5iwDlENBlmY"; 
const char* mqttTopic = "v1/devices/me/telemetry";

// DHT11 Sensor details
#define DHTPIN 13     
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Create a WiFi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  setupWiFi();

  // Setup MQTT client
  client.setServer(mqttServer, mqttPort);
  
  // Connect to MQTT broker
  connectMQTT();

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Ensure the client is connected
  if (!client.connected()) {
    connectMQTT();
  }

  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Create a JSON message
  String message = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";
  
  // Publish the message
  if (client.publish(mqttTopic, message.c_str())) {
    Serial.print("Published: ");
    Serial.println(message);
  } else {
    Serial.println("Message failed to send");
  }

  // Wait a bit before sending the next message
  delay(5000); // Adjust the delay as needed
}

void setupWiFi() {
  delay(10);
  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected.");
}

void connectMQTT() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", mqttUser, "")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
