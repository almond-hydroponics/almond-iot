#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>

#include "ESPAsyncWebServer.h"

#include "config.h"
#include "logger.h"

AsyncWebServer server(80);


#ifndef STASSID
#define STASSID CONFIG.wlan.ssid
#define STAPSK  CONFIG.wlan.password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Global Variables
WiFiClient httpClient;
WiFiClientSecure securedClient;
ESP8266WiFiMulti wifiMulti;


const int led = PIN_LED;

void wifiOnConnect()
{
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
}

void loginToWifi()
{
    WiFi.mode(WIFI_STA);

    wifiMulti.addAP(CONFIG.wlan.ssid, CONFIG.wlan.password);

    Serial.println("Connecting Wifi...");
    while (wifiMulti.run() != WL_CONNECTED) {
        wifiOnConnect();
        Serial.print(".");
        delay(1000);
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    digitalWrite(led, HIGH);
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);

    Serial.println("=====loginToWifi=====");
    loginToWifi();

    server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello from ESP8266 server route");
    });

    server.on("/redirect/internal", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("/hello");
    });

    server.on("/redirect/external", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("https://almond-re.herokuapp.com/");
    });

    server.begin();
}

void loop()
{

}

