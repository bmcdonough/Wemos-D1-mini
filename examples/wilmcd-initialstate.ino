// The MIT License (MIT)

// Copyright (c) 2016 Bill McDonough

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


//#include <AmazonIOTClient.h>
//#include <ESP8266AWSImplementations.h>
//#include <AWSFoundationalTypes.h>
#include <Wire.h>
#include <SDL_Arduino_INA3221.h>
SDL_Arduino_INA3221 ina3221;
// Use WiFiClient class to create TCP connections
#include <ESP8266WiFi.h>
WiFiClient client;
//WILMCD: add a keys.cpp and add values for everything that's in keys.h
#include "keys.h"


const int sleepTimeS = 60;

void printWiFiData();
void printCurrentNetwork();
bool switchIsDisabled();
void publish(const char *topic, uint16_t data);
void checkDigitalVoltage();


////////////////////////////
// Initial State Streamer //
////////////////////////////

// Data destination
// https can't be handled by the ESP8266, thus "insecure"
#define ISDestURL "insecure-groker.initialstate.com"
// Bucket key (hidden reference to your bucket that allows appending):
#define bucketKey "SDJJGNSS68LB"
// Bucket name (name your data will be associated with in Initial State):
#define bucketName "F150"
// Access key (the one you find in your account settings):
#define accessKey "fBt7dSCtjsOD5bNMoCzGHQ0m27GSkwNo"
// How many signals are in your stream? You can have as few or as many as you want
const int NUM_SIGNALS = 13;
// What are the names of your signals (i.e. "Temperature", "Humidity", etc.)
String signalName[NUM_SIGNALS] = {"RSSI", "1LIPO_Battery Bus Voltage V", "1LIPO_Battery Shunt Voltage mV", "1LIPO_Battery Load Voltage V", "1LIPO_Battery Current mA", "Solar Cell Bus Voltage V", "Solar Cell Shunt Voltage mV", "Solar Cell Load Voltage V", "Solar Cell Current mA", "Car_Battery Bus Voltage V", "Car_Battery Shunt Voltage mV", "Car_Battery Load Voltage V", "Car_Battery Current mA"};
// This array is to store our signal data later
String signalData[NUM_SIGNALS];

/////////////
// Signals //
////////////

//Signal number 1
int i = 0;
//Signal number 2
bool increase = true;

// the three channels of the INA3221 named for SunAirPlus Solar Power Controller channels (www.switchdoc.com)
#define LIPO_BATTERY_CHANNEL 1
#define SOLAR_CELL_CHANNEL 2
#define OUTPUT_CHANNEL 3


void setup() {
  Serial.begin(9600);

  // Pin configuration
//  pinMode(sensorEnable, OUTPUT);
//  pinMode(sensorSwitch, INPUT);

  Serial.println("Started!");

  Serial.println("Measuring voltage and current with ina3221 ...");
  ina3221.begin();

  setupwiffy();
  checkDigitalVoltage();
  Serial.println("SleepyTime");
  ESP.deepSleep(sleepTimeS * 1000000);
}


void loop() {
}


void printWiFiData() {
  // IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}


void printCurrentNetwork() {
  // SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // signal strength:
  Serial.print("signal strength (RSSI): ");
  Serial.println(WiFi.RSSI());
}


bool sensorIsDisabled() {

//  return digitalRead(sensorSwitch) == LOW;
}

void setupwiffy()
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(wifiSsid);
  Serial.println("...");

  int wifi_counter = 0;

  WiFi.begin(wifiSsid, wifiPwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
    wifi_counter++;
    if (wifi_counter > 200) {
      Serial.println("\nno Wiffy, SleepyTime");
      ESP.deepSleep(sleepTimeS * 1000000);
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");

  printCurrentNetwork();
  printWiFiData();

  delay(50);
}



void publish(const char *topic, float data) {

  //AmazonIOTClient iotClient;
  //ActionError actionError;

  //Esp8266HttpClient httpClient;
  //Esp8266DateTimeProvider dateTimeProvider;

  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(wifiSsid);
  Serial.println("...");

  WiFi.begin(wifiSsid, wifiPwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  Serial.println("");
  Serial.println("WiFi connected");

  printCurrentNetwork();
  printWiFiData();

  delay(50);

  Serial.println("Initializing IoT client...");

  //iotClient.setAWSRegion(awsIotRegion);
  //iotClient.setAWSEndpoint(awsIotEndpoint);
  //iotClient.setAWSDomain(awsIotDomain);
  //iotClient.setAWSPath("/things/digital-voltage/shadow");
  //iotClient.setAWSKeyID(awsKeyID);
  //iotClient.setAWSSecretKey(awsSecKey);
  //iotClient.setHttpClient(&httpClient);
  //iotClient.setDateTimeProvider(&dateTimeProvider);

  delay(50);

  Serial.println("Updating thing shadow...");

  //MinimalString shadow = ("{\"state\":{\"reported\":{\"" + String(topic) + "\":" + String(data, 2) + "}}}").c_str();
  //char* result = iotClient.update_shadow(shadow, actionError);
  delay(50);

  Serial.print("sizeof_result: ");
  //Serial.println(sizeof(result));

  Serial.print("result: ");
  //Serial.println(result);
}


// this method makes a HTTP connection to the server and creates a bucket is it does not exist:
bool postBucket() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(ISDestURL, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    // Build HTTP request.
    String toSend = "POST /api/buckets HTTP/1.1\r\n";
    toSend += "Host:";
    toSend += ISDestURL;
    toSend += "\r\n" ;
    toSend += "User-Agent:Arduino\r\n";
    toSend += "Accept-Version: ~0\r\n";
    toSend += "X-IS-AccessKey: " accessKey "\r\n";
    toSend += "Content-Type: application/json\r\n";
    String payload = "{\"bucketKey\": \"" bucketKey "\",";
    payload += "\"bucketName\": \"" bucketName "\"}";
    payload += "\r\n";
    toSend += "Content-Length: "+String(payload.length())+"\r\n";
    toSend += "\r\n";
    toSend += payload;

    client.println(toSend);
    Serial.println(toSend);

    return true;
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    return false;
  }
}


// this method makes a HTTP connection to the server and sends the signals measured:
bool postData() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(ISDestURL, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    // Build HTTP request.
    // Build HTTP request.

  for (int i=0; i<NUM_SIGNALS; i++){
    String toSend = "POST /api/events HTTP/1.1\r\n";
    toSend += "Host:";
    toSend += ISDestURL;
    toSend += "\r\n" ;
    toSend += "Content-Type: application/json\r\n";
    toSend += "User-Agent: Arduino\r\n";
    toSend += "Accept-Version: ~0\r\n";
    toSend += "X-IS-AccessKey:  " accessKey "\r\n";
    toSend += "X-IS-BucketKey:  " bucketKey "\r\n";

      String payload = "[{\"key\": \"" + signalName[i] + "\", ";
      payload +="\"value\": \"" + signalData[i] + "\"}]\r\n";

    toSend += "Content-Length: " + String(payload.length())+"\r\n";
    toSend += "\r\n";
    toSend += payload;

    Serial.println(toSend);
    client.println(toSend);

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
      }
    }

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");


  }
  return true;
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    return false;
  }
}


void checkDigitalVoltage() {
  Serial.println("------------------------------");
  float shuntvoltage1 = 0;
  float busvoltage1 = 0;
  float current_mA1 = 0;
  float loadvoltage1 = 0;


  busvoltage1 = ina3221.getBusVoltage_V(LIPO_BATTERY_CHANNEL);
  shuntvoltage1 = ina3221.getShuntVoltage_mV(LIPO_BATTERY_CHANNEL);
  current_mA1 = -ina3221.getCurrent_mA(LIPO_BATTERY_CHANNEL);  // minus is to get the "sense" right.   - means the battery is charging, + that it is discharging
  loadvoltage1 = busvoltage1 + (shuntvoltage1 / 1000);

  Serial.print("LIPO_Battery Bus Voltage:   "); Serial.print(busvoltage1); Serial.println(" V");
  Serial.print("LIPO_Battery Shunt Voltage: "); Serial.print(shuntvoltage1); Serial.println(" mV");
  Serial.print("LIPO_Battery Load Voltage:  "); Serial.print(loadvoltage1); Serial.println(" V");
  Serial.print("LIPO_Battery Current 1:       "); Serial.print(current_mA1); Serial.println(" mA");
  Serial.println("");

  float shuntvoltage2 = 0;
  float busvoltage2 = 0;
  float current_mA2 = 0;
  float loadvoltage2 = 0;

  busvoltage2 = ina3221.getBusVoltage_V(SOLAR_CELL_CHANNEL);
  shuntvoltage2 = ina3221.getShuntVoltage_mV(SOLAR_CELL_CHANNEL);
  current_mA2 = -ina3221.getCurrent_mA(SOLAR_CELL_CHANNEL);
  loadvoltage2 = busvoltage2 + (shuntvoltage2 / 1000);

  Serial.print("Solar Cell Bus Voltage 2:   "); Serial.print(busvoltage2); Serial.println(" V");
  Serial.print("Solar Cell Shunt Voltage 2: "); Serial.print(shuntvoltage2); Serial.println(" mV");
  Serial.print("Solar Cell Load Voltage 2:  "); Serial.print(loadvoltage2); Serial.println(" V");
  Serial.print("Solar Cell Current 2:       "); Serial.print(current_mA2); Serial.println(" mA");
  Serial.println("");

  float shuntvoltage3 = 0;
  float busvoltage3 = 0;
  float current_mA3 = 0;
  float loadvoltage3 = 0;

  busvoltage3 = ina3221.getBusVoltage_V(OUTPUT_CHANNEL);
  shuntvoltage3 = ina3221.getShuntVoltage_mV(OUTPUT_CHANNEL);
  current_mA3 = ina3221.getCurrent_mA(OUTPUT_CHANNEL);
  loadvoltage3 = busvoltage3 + (shuntvoltage3 / 1000);

  Serial.print("Output Bus Voltage 3:   "); Serial.print(busvoltage3); Serial.println(" V");
  Serial.print("Output Shunt Voltage 3: "); Serial.print(shuntvoltage3); Serial.println(" mV");
  Serial.print("Output Load Voltage 3:  "); Serial.print(loadvoltage3); Serial.println(" V");
  Serial.print("Output Current 3:       "); Serial.print(current_mA3); Serial.println(" mA");
  Serial.println("");

  //publish("busvoltage1", busvoltage1);
  // Gather Data
  // Read from a port for input or output or generate your own values/messages
  signalData[0] = WiFi.RSSI();
  signalData[1] = String(busvoltage1, 2);
  signalData[2] = String(shuntvoltage1, 2);
  signalData[3] = String(loadvoltage1, 2);
  signalData[4] = String(current_mA1, 2);
  signalData[5] = String(busvoltage2, 2);
  signalData[6] = String(shuntvoltage2, 2);
  signalData[7] = String(loadvoltage2, 2);
  signalData[8] = String(current_mA2, 2);
  signalData[9] = String(busvoltage3, 2);
  signalData[10] = String(shuntvoltage3, 2);
  signalData[11] = String(loadvoltage3, 2);
  signalData[12] = String(current_mA3, 2);

  // The postData() function streams our events
  while(!postData());

  // Wait for 1 seconds before collecting and sending the next batch
  delay(1000);
}
