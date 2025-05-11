#include <esp_now.h>
#include <WiFi.h>
#include <SPI.h>
#include <Stepper.h>
#include <ESP32Servo.h>

Servo servo1;  // Servo seed dispensing blue
Servo servo2;  // Servo retraction black

unsigned long lastPumpTime = 0;
const unsigned long interval = 86400000; // 24 hours

const int steps = 200;
Stepper sx(steps, 5, 18, 19, 21);
Stepper sz(steps, 15, 4, 22, 23);
int pumpPin = 13;

// Global variable for servo1 angle
int seedServoAngle = 0;

typedef struct struct_message {
  int id;
  float temp;
  float hum;
} struct_message;

struct_message myData;
struct_message board1;
struct_message boardsStruct[3] = {board1};

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           info->src_addr[0], info->src_addr[1], info->src_addr[2],
           info->src_addr[3], info->src_addr[4], info->src_addr[5]);
  Serial.printf("Packet received from: %s\n", macStr);

  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %d: %d bytes\n", myData.id, len);

  boardsStruct[myData.id - 1].temp = myData.temp;
  boardsStruct[myData.id - 1].hum = myData.hum;

  Serial.println("Board 1:");
  Serial.printf("Temp: %.2f, Hum: %.2f\n", boardsStruct[0].temp, boardsStruct[0].hum);
}

void setup() {
  Serial.begin(115200);
  servo1.attach(32);
  servo2.attach(33);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
  sx.setSpeed(80);
  sz.setSpeed(80);

  Serial.println("ESPNow/Basic/Slave Example");

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

int i=0;
void loop() {
  float board1X = boardsStruct[0].temp;
  float board1Y = boardsStruct[0].hum;

  Serial.print("Room1_T: ");
  Serial.println(board1X);
  Serial.print("Room1_H: ");
  Serial.println(board1Y);

  unsigned long currentTime = millis();

  // Uncomment for timed or condition-based watering
  if (currentTime - lastPumpTime >= interval) {
    wateringSequence();
    lastPumpTime = currentTime;
  }
  if (board1X >= 30) {
    wateringSequence();
  }

  while (i < 1) {
    seedDroppingSequence();
    i++;
  }

  delay(1000);
}

void seedDroppingSequence() {
  downretract();
  for (int i = 0; i < 3; i++) {
    positionf();
    delay(100);
    servoDrop();
    delay(1000);
  }
  retract();
  delay(1000);
  positionri();
  downretract();
  for (int i = 0; i < 3; i++) {
    positionre();
    delay(100);
    servoDrop();
    delay(1000);
  }
  retract();
  delay(1000);
  positionri();
  downretract();
  for (int i = 0; i < 3; i++) {
    positionf();
    delay(100);
    servoDrop();
    delay(1000);
  }
  retract();
  delay(1000);
  startPosition();
}

void wateringSequence() {
  for (int i = 0; i < 3; i++) {
    positionf();
    delay(100);
    water();
    delay(1000);
  }
  positionri();
  water();
  for (int i = 0; i < 3; i++) {
    positionre();
    delay(100);
    water();
    delay(1000);
  }
  positionri();
  water();
  for (int i = 0; i < 3; i++) {
    positionf();
    delay(100);
    water();
    delay(1000);
  }
  startPosition();
}

void positionf() {
  sx.step(-500);
}

void positionf1() {
  sx.step(-1500);
}

void positionri() {
  sz.step(500);
}

void positionre() {
  sx.step(500);
}

void positionre1() {
  sx.step(1500);
}

void startPosition() {
  sz.step(-1500);
  sx.step(1500);
}

void water() {
  digitalWrite(pumpPin, HIGH);
  delay(1000);
  digitalWrite(pumpPin, LOW);
}

void servoDrop() {
  seedServoAngle += 15;
  if (seedServoAngle > 360) {
    seedServoAngle = 360;
  }
  Serial.printf("Rotating servo1 to %d degrees...\n", seedServoAngle);
  servo1.write(seedServoAngle);
  delay(1000);
}

void retract() {
  // Serial.println("Moving servo2 to 0 degrees...");
  // servo2.write(0);
  // delay(1000);

  Serial.println("Moving servo2 to 90 degrees...");
  servo2.write(90);
  delay(2000);
}

void downretract() {
  // Serial.println("Moving servo2 to 90 degrees...");
  // servo2.write(90);
  // delay(1000);

  Serial.println("Moving servo2 to 0 degrees...");
  servo2.write(0);
  delay(1000);
}
