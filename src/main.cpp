#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL670vbMUX0"
#define BLYNK_TEMPLATE_NAME "pakan kucing"
#define BLYNK_AUTH_TOKEN "9ManuX5fBpmheqdf_3M-LaVZyGyoe4DM"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN; // token dapat dicek di email
char ssid[] = "..";             // nama wifi
char pass[] = "12345678";       // password wifi

Servo servo;
int pinServo = 2;
int pos = 0;
int maxAngle = 90;

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

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}