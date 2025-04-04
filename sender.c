#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Tomj";
const char* password = "12345676";

// Receiver (the other ESP8266)'s IP and port
const char* receiverIP = "192.168.12.117";  // Update this if different
const unsigned int receiverPort = 4210;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");
  Serial.print("📡 Sender IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Generate a random number
  int randomNumber = random(0, 1000);
  char buffer[10];
  sprintf(buffer, "%d", randomNumber);

  // Send via UDP
  udp.beginPacket(receiverIP, receiverPort);
  udp.write(buffer);
  udp.endPacket();

  Serial.printf("📤 Sent: %s to %s:%d\n", buffer, receiverIP, receiverPort);
  
  delay(2000);  // Wait 2 seconds
}
