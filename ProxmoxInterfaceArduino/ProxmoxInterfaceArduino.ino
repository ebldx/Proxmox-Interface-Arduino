#include <R4HttpClient.h>

WiFiSSLClient client;
R4HttpClient http;

const char* _SSID = "WIFI SSID";
const char* _PASSWORD = "PASSWORD";

const uint16_t PVE_PORT = 8006;
const char* PVE_HOST = "192.168.0.00";
const char* NODE_NAME = "your-node-name";

const String URL = String("https://") + PVE_HOST + "/api2/json/nodes/" + NODE_NAME + "/status";

const char* PVE_USER = "root@pam";
const char* TOKEN_ID = "your-token-id";
const char* TOKEN_SECRET = "your-token-secret";


void setup() {
  Serial.begin(9600);

  WiFi.begin(_SSID, _PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.println("Connected!");

  http.begin(client, URL, PVE_PORT);
  http.setTimeout(3000);

  http.addHeader(String("Authorization: PVEAPIToken=") + PVE_USER + "!" + TOKEN_ID + "=" + TOKEN_SECRET);
  http.addHeader("Accept: application/json");

  int responseCode = http.GET();

  if (responseCode == HTTP_CODE_OK) {
    Serial.println(http.getBody());
    Serial.print("Response code: ");
    Serial.println(responseCode);
  } else {
    Serial.print("Request failed: ");
    Serial.println(responseCode);
  }

  http.close();
}

void loop() {

}