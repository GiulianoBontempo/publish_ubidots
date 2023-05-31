/******************************************
 *
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsEsp32Mqtt.h"

/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBFF-L2UWDy9jLghHCxu8o0xL10OjOrWxcM";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "Inteli-COLLEGE";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "QazWsx@123";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "giuliano_ponderada";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "decibeis"; // Put here your Variable label to which data  will be published

const int PUBLISH_FREQUENCY = 2000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if ((millis() - timer) > (PUBLISH_FREQUENCY))
  {
    float signalStrength = WiFi.RSSI();
    Serial.println(signalStrength);
    ubidots.add(VARIABLE_LABEL, signalStrength);
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
}
