#include <WiFi.h>
#include <WiFi.h>
#include <PubSubClient.h>

/* WIFI CREDENTIALS */ 
  const char* ssid = "YOUR_SSID"; /* REPLACE WITH YOUR WIFI SSID */ 
  const char* password = "YOUR_PASSWORD"; /* REPLACE WITH YOUR WIFI PASSWORD */ 


/* THINGSBOARD CREDENTIALS */ 
  const char* mqttServer = "chiptree-iot.aifarm.dev";
  const int mqttPort = 1883;
  const char* mqttUser = "YOUR_THINGSBOARD_TOKEN"; /* YOUR THINGSBOARD TOKEN */ 
  const char* telemetryTopic = "v1/devices/me/telemetry";

/* CREATE WIFI AND MQTT CLIENTS */ 
  WiFiClient wifiClient;
  PubSubClient mqttClient(wifiClient);

void setup() {
  /* START SERIAL MONITOR */ 
    Serial.begin(115200);

  /* CONNECT TO WIFI */ 
    connectToWiFi();

  /* SET MQTT SERVER */ 
   mqttClient.setServer(mqttServer, mqttPort);
}

void loop() {
  /* ENSURE THE CLIENT IS CONNECTED */ 
    if (!mqttClient.connected()) {
      reconnect();
    }
    mqttClient.loop();

  /* PUBLISH TELEMETRY DATA */ 
    publishTelemetry();

  /* DELAY BEFORE THE NEXT PUBLISH */ 
    delay(5000); /* ADJUST THE DELAY AS NEEDED */ 
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi");
}

void reconnect() {
  /* LOOP UNTIL WE'RE RECONNECTED */ 
    while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    /* ATTEMPT TO CONNECT */ 
      if (mqttClient.connect("ESP32Client", mqttUser, nullptr)) {
        Serial.println("connected");
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 5 seconds");
        delay(5000);
      }
  }
}

void publishTelemetry() {
  /* CREATE JSON PAYLOAD */ 
     String payload = "{\"temperature\":25}"; /* ADJUST TEMPERATURE VALUE AS NEEDED */ 

  /* PUBLISH THE MESSAGE */ 
    if (mqttClient.publish(telemetryTopic, payload.c_str())) {
      Serial.println("Telemetry published: " + payload);
    } else {
      Serial.println("Telemetry publish failed");
    }
}
