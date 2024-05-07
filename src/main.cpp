#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6WTerXsMv"
#define BLYNK_TEMPLATE_NAME "Kucing"
#define BLYNK_AUTH_TOKEN ""

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <WiFiManager.h>

char WiFi_SSID[] = "Esp8266-Servo";
char WiFi_PASS[] = "default*";
char auth[] = BLYNK_AUTH_TOKEN;

Servo servo;
int pinServo = 2;
int maxAngle = 180;
int pos = 0;

BlynkTimer timer;

WiFiManager wifiManager;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1);
}

BLYNK_WRITE(V1) {
  int pinValue1 = param.asInt();
  Serial.println(pinValue1);
  if (pinValue1 == 0) {
    servo.attach(pinServo);
    for (pos = 0; pos <= maxAngle; pos++) {
      servo.write(pos);
      delay(10);
    }
    servo.detach();
  } else if (pinValue1 == 1) {
    servo.attach(pinServo);
    for (pos = maxAngle; pos >= 0; pos--) {
      servo.write(pos);
      delay(10);
    }
    servo.detach();
  }
}

// write posisi servo di blynk app
void sendServoAngle() {
  Blynk.virtualWrite(V2, pos);
}

void setup() {
  Serial.begin(115200);

  wifiManager.autoConnect(WiFi_SSID,WiFi_PASS);

  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
  timer.setInterval(5000L, sendServoAngle);
}

void loop() {
  Blynk.run();
  timer.run();
}