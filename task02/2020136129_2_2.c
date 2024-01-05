int red = 6;
int yellow = 7;
int green = 8;
int blue = 9;
int white = 10;
int trigPin = 11;
int echoPin = 12;
long duration, cm;

void setup() {
  Serial.begin (9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) * 0.0343;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm <= 40){
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(white, LOW);
  }
  else if(cm <= 45){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(white, LOW);
  }
  else if(cm <= 50){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(white, LOW);
  }
  else if(cm <= 55){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(white, LOW);
  }
  else if(cm <= 60){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(white, LOW);
  }
  else if(cm >= 61){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(white, HIGH);
  }
  delay(100);

}