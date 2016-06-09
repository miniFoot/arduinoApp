#include <Adafruit_NeoPixel.h>

#include <Process.h>
#include <Bridge.h>
#define ledPin  13
Process process;

int trig = 12;
int echo = 11;

int trig2 = 7;
int echo2 = 6;

long lecture_echo, lecture_echo2;
long cm;
long cm2 ;
long timeSinceTweet, timeSinceData;
int lastDistSensor;

String url = "http://5.196.7.169:8080/newgoal";
String myTweet ;
int freqTweet = 4000;
bool starting;

/* NEO PIXEL PART */
#define PIXEL_PIN 10
#define PIXEL_COUNT 10
#define PIXEL_TYPE  NEO_GRB 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

#define PIXEL_PIN2 9
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN2, PIXEL_TYPE);

void setup()
{
  Bridge.begin();

  strip.begin();
  strip.show();

  strip2.begin();
  strip2.show();


  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
   pinMode(echo, INPUT);
  pinMode(trig2, OUTPUT);
  digitalWrite(trig2, LOW);
  pinMode(echo2, INPUT);
  Serial.begin(9600);

  timeSinceData = 0;
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop()
{

  pinMode(ledPin, OUTPUT);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo, HIGH);
  cm = lecture_echo / 58;

  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  lecture_echo2 = pulseIn(echo2, HIGH);

  cm2 = lecture_echo2 / 58;
  if(cm > 1){
    if (cm < 18  ) {
      if ((millis() - timeSinceData) > freqTweet) {
        for (int i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 25, 25, 250);
        }
        strip.show();
        tweetPing("1");
        timeSinceData = millis();
        delay(4000);
         for (int i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 0);
         }
         strip.show();
      }
    }
  }
  if(cm2 > 1){
    if (cm2 < 18 ) {
      if ((millis() - timeSinceData) > freqTweet) {
        for (int i = 0; i < strip2.numPixels(); i++) {
          strip2.setPixelColor(i, 250, 25, 25);
        }
        strip2.show();
        tweetPing("0");
        timeSinceData = millis();
        delay(4000);
        for (int i = 0; i < strip.numPixels(); i++) {
          strip2.setPixelColor(i, 0, 0, 0);
         }
         strip2.show();
      }
    }
  }
  Serial.print("Distancem : ");
  Serial.println(cm);
  Serial.println(cm2);
  delay(10);
}
void tweetPing(String Tweet) {
  digitalWrite(ledPin, HIGH);
  Process p;
  String curlCmd;
  curlCmd = "curl " ;
  curlCmd += "-X POST -d \"";
  curlCmd += "redGoal=" ;
  curlCmd += Tweet;
  curlCmd += "\" " ;
  curlCmd += url;
  p.runShellCommand(curlCmd);
  Serial.println("Posting");
  delay(4000);
  Serial.println(curlCmd);
  Serial.println(Tweet) ;
  myTweet = "";
  // Reset des pararmètres
  timeSinceTweet = millis();

}
