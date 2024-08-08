#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = ""; // Update with your WiFi SSID
const char* pass = ""; // Update with your WiFi Password

const char* serverName = "http://yourIP/Robotproj/file.php"; // Update with your server URL
const int ledPin = 5; // Change to your LED pin

unsigned long interval = 10000; // Check every 10 seconds
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Make HTTP GET request
    HTTPClient http;
    http.begin(serverName);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.print("Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("Payload: ");
      Serial.println(payload);
      
      // Check if the response is "forward"
      if (payload.indexOf("forward") != -1) {
        blinkLED();
      }
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
}

void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
