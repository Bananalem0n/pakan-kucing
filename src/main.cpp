#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6WTerXsMv"
#define BLYNK_TEMPLATE_NAME "Kucing"
#define BLYNK_AUTH_TOKEN "x157tfHtNqjX-PCk-aITZ22cgOnyLUYC"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN; // token dapat dicek di email
char ssid[] = "..";             // nama wifi
char pass[] = "12345678";       // password wifi

Servo servo; // initiate servo class library
int pinServo = 2; // servo pin on microcontroller
int maxAngle = 180; // angle servo max

int pos = 0;

BlynkTimer timer;

BLYNK_CONNECTED() {
   Blynk.syncVirtual(V1);
}

BLYNK_WRITE(V1)
{
  int pinValue1 = param.asInt();
  Serial.println(pinValue1);
  if (pinValue1 == 0)
  {
    servo.attach(pinServo);
    for (pos = 0; pos <= maxAngle; pos++)
    {
      servo.write(pos);
      delay(10);
    }
    servo.detach();
  }
  else if (pinValue1 == 1)
  {
    servo.attach(pinServo);
    for (pos = maxAngle; pos >= 0; pos--)
    {
      servo.write(pos);
      delay(10);
    }
    servo.detach();
  }
}

void sendServoAngle()
{
  Blynk.virtualWrite(V2, pos); // Send servo angle to virtual pin 2
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, sendServoAngle); // Set timer to trigger every 5 seconds
}

void loop()
{
  Blynk.run();
  timer.run(); // Run Blynk timer
}
