/* Utilisation du capteur Ultrason HC-SR04 */

// définition des broches utilisées 
int trig = 12; 
int echo = 11; 
long lecture_echo; 
long cm;

void setup() 
{ 
  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() 
{ 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 
  Serial.print("Distancem : "); 
  Serial.println(cm); 
  delay(10); 
}
