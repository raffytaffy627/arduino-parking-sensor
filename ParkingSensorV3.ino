// Pins
const int trigPin = 12;
const int echoPin = 11;
const int greenPin = 5;
const int yellowPin = 6;
const int redPin = 7;
const int buzzerPin = 8;

// Distance zones (in cm)
const int SAFE_DISTANCE = 30;
const int WARNING_DISTANCE = 15;
const int DANGER_DISTANCE = 5;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

long readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration / 58;
}

void beep(int length) {
  digitalWrite(buzzerPin, HIGH);
  delay(length);
  digitalWrite(buzzerPin, LOW);
}

void allOff() {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  long distance = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  allOff();

  if (distance == 0 || distance > SAFE_DISTANCE) {
    // Safe: green, no sound
    digitalWrite(greenPin, HIGH);
    delay(100);
  } else if (distance > WARNING_DISTANCE) {
    // Getting close: yellow, slow beeps
    digitalWrite(yellowPin, HIGH);
    beep(50);
    delay(distance * 15);
  } else if (distance > DANGER_DISTANCE) {
    // Close: red, fast beeps
    digitalWrite(redPin, HIGH);
    beep(50);
    delay(distance * 10);
  } else {
    // Too close: red, nonstop tone
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
  }
}
