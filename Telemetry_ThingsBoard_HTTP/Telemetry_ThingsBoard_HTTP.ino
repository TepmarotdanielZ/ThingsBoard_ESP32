
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DREAMSLAB UNIFI";
const char* password = "@DREAMSLAB2023";

// ThingsBoard server configuration with your TOKEN:
const char* serverName = "http://demo.thingsboard.io/api/v1/cNBxUhUuKHzzt734YUuL/telemetry";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  int wifiRetry = 0;
  while (WiFi.status() != WL_CONNECTED && wifiRetry < 20) {
    delay(500);
    Serial.print(".");
    wifiRetry++;
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi");
    return;
  }
  
  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sendTelemetry();
  delay(5000);
}

void sendTelemetry() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    WiFi.reconnect();
    return;
  }

  HTTPClient http;

  Serial.println("Preparing HTTP POST...");
  Serial.print("Connecting to: ");
  Serial.println(serverName);

  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");

  String jsonData = "{\"temperature\":256}";
  Serial.println("Sending JSON: " + jsonData);

  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println("Response: " + response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    Serial.print("Error details: ");
    Serial.println(http.errorToString(httpResponseCode).c_str());
  }

  http.end();
}