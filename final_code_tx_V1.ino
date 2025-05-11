#include <WiFi.h> 
#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>                // Install DHT library by adafruit 1.3.8

#include <esp_now.h>
#define DHT_SENSOR_PIN 4
#define DHT_SENSOR_TYPE DHT11

//To provide the ESP32 / ESP8266 with the connection and the sensor type
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

uint8_t broadcastAddress[] = {0x10, 0x06, 0x1c, 0x82, 0x01, 0x88};

typedef struct {
  int id;
  float temp;
  float hum;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Theja"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDMt-BdFVoWYEdoBGviq8zlk8kDwqgcZWk"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://dhtnew-5c880-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;                     //since we are doing an anonymous sign in 

void setup(){

  dht_sensor.begin();
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  //memset(&myData, 0, sizeof(myData));
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

}

void loop(){

  //temperature and humidity measured should be stored in variables so the user
  //can use it later in the database

  float temperature = dht_sensor.readTemperature();
  float humidity = dht_sensor.readHumidity();
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    //since we want the data to be updated every second
    sendDataPrevMillis = millis();
    // Enter Temperature in to the DHT_11 Table
    if (Firebase.RTDB.setInt(&fbdo, "DHT_11/Temperature", temperature)){
      // This command will be executed even if you dont serial print but we will make sure its working
      Serial.print("Temperature : ");
      Serial.print(temperature);
      Serial.print("\n");
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    
    // Enter Humidity in to the DHT_11 Table
    if (Firebase.RTDB.setFloat(&fbdo, "DHT_11/Humidity", humidity)){
      Serial.print("Humidity : ");
      Serial.print(humidity);
      Serial.print("\n");
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    }

  myData.id = 1;
  myData.temp = temperature;
  myData.hum = humidity;

  Serial.print("Sending: "); Serial.println(myData.temp);
  Serial.print("Sendingx: "); Serial.println(temperature);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(200);
}
