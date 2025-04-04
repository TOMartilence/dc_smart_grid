#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Tomj";
const char* password = "12345676";

WiFiUDP udp;
const unsigned int localUdpPort = 4210;  // Same as sender's target port
char incomingPacket[255];  // buffer for incoming packets

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
  Serial.print("📥 Receiver IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(localUdpPort);
  Serial.printf("📡 Listening on UDP port %d\n", localUdpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }
    Serial.printf("📨 Received: %s from %s:%d\n", incomingPacket, udp.remoteIP().toString().c_str(), udp.remotePort());
  }
}
