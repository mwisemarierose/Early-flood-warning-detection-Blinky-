#define BLYNK_TEMPLATE_ID "TMPL2yCXllLh8"
#define BLYNK_TEMPLATE_NAME "ESP32 Water Level"
#define BLYNK_AUTH_TOKEN "VBhchb_Mc39NgxzjvK35Chww293mF8vs"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
//#include <BlynkTimer.h>

char ssid[] = "Rose";
char pass[] = "12345678";
const int trigPin = 5;
const int echoPin = 18;
const int buzzerPin = 15;

#define SOUND_SPEED 0.034

int blue = 13;
int red = 14;
int yellow = 12;
long duration;
float distanceCm;
float distanceMeters;
BlynkTimer timer;

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Blynk.virtualWrite(V1, value);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
  timer.setInterval(1000L, myTimerEvent);
}

void myTimerEvent()
{
  Blynk.virtualWrite(V2, distanceCm);
  float percentage = map(distanceCm, 10, 40, 0, 100); // Adjust the mapping if needed
  Blynk.virtualWrite(V1, percentage);

  if (distanceCm <= 6) {
    digitalWrite(red, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Blynk.virtualWrite(V3, HIGH);
    Blynk.virtualWrite(V4,LOW);
    Blynk.virtualWrite(V5,LOW);
    
    digitalWrite(yellow, LOW);
    digitalWrite(blue, LOW);
  } else if (distanceCm <= 12) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(buzzerPin, LOW);
    Blynk.virtualWrite(V5, HIGH);
    Blynk.virtualWrite(V4,LOW);
    Blynk.virtualWrite(V3,LOW);
  } else {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(buzzerPin, LOW);
    Blynk.virtualWrite(V4, HIGH);
    Blynk.virtualWrite(V3,LOW);
    Blynk.virtualWrite(V5,LOW);
  }
}

void loop()
{
  Blynk.run();
  timer.run();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  distanceMeters = distanceCm / 100.0; // Convert cm to meters

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

}
