const int trigPin = 12;
const int echoPin = 11;
const int greenPin = 5;
const int yellowPin = 6;
const int redPin = 7;
const int buzzerPin = 8;

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

void loop() {
  long distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Turn everything off first
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(buzzerPin, LOW);

  if (distanceCm == 0 || distanceCm > 30) {
    // Nothing close: safe
    digitalWrite(greenPin, HIGH);
  } else if (distanceCm > 15) {
    // Between 16 and 30 cm: getting close
    digitalWrite(yellowPin, HIGH);
  } else {
    // 15 cm or less: too close
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);
}
