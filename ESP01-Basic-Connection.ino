#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";

int connectionTime = 0;

void setup() {
  Serial.begin(74880);
  Serial.println("ESP-01 Script Initialized");
  
  uint8_t macAddr[6];
  WiFi.macAddress(macAddr);
  Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting to wireless access point with SSID ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED && connectionTime < 30) {
    delay(500);
    Serial.print(".");
    connectionTime++;
  }

  if (connectionTime >= 30) {
    Serial.println("Connection timed out. Access point may be unavailavle.");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("OK");
    Serial.println();
    Serial.println("Network Configuration ");
    Serial.println("=============================================");
    Serial.print("Hostname: ");
    Serial.println(WiFi.hostname());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.printf("Gataway: %s\n", WiFi.gatewayIP().toString().c_str());
    Serial.print("Subnet: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("DNS: ");
    WiFi.dnsIP().printTo(Serial);
  }
  else
  {
    listNetworks();
  }
}

void loop() {

}

void listNetworks() {
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't connect to a network.");
    while (true);
  }
  
  Serial.print(numSsid);
  Serial.println(" wireless networks available.");

  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.println(" dBm");
  }
}
