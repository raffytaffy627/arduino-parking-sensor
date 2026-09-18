// Sensor
const int trigPin = 12;
const int echoPin = 11;

// LEDs and buzzer
const int greenPin = 5;
const int yellowPin = 6;
const int redPin = 7;
const int buzzerPin = 8;

// Display
const bool COMMON_CATHODE = true;
const int segmentPins[8] = {29, 33, 25, 23, 22, 30, 26, 24}; // A,B,C,D,E,F,G,DP
const int digitPins[4] = {28, 31, 32, 27}; // D1,D2,D3,D4

const byte numbers[10] = {
  B00111111, B00000110, B01011011, B01001111, B01100110,
  B01101101, B01111101, B00000111, B01111111, B01101111
};

unsigned long lastReadTime = 0;
int currentDistance = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < 8; i++) pinMode(segmentPins[i], OUTPUT);
  for (int d = 0; d < 4; d++) { pinMode(digitPins[d], OUTPUT); digitOff(d); }

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

void setSegments(byte pattern) {
  for (int i = 0; i < 8; i++) {
    bool on = bitRead(pattern, i);
    if (!COMMON_CATHODE) on = !on;
    digitalWrite(segmentPins[i], on ? HIGH : LOW);
  }
}
void digitOn(int d)  { digitalWrite(digitPins[d], COMMON_CATHODE ? LOW : HIGH); }
void digitOff(int d) { digitalWrite(digitPins[d], COMMON_CATHODE ? HIGH : LOW); }

void showNumber(int value) {
  int digits[4] = {(value/1000)%10, (value/100)%10, (value/10)%10, value%10};
  for (int d = 0; d < 4; d++) {
    setSegments(numbers[digits[d]]);
    digitOn(d);
    delay(3);
    digitOff(d);
  }
}

void loop() {
  if (millis() - lastReadTime >= 200) {
    currentDistance = readDistanceCm();
    lastReadTime = millis();

    Serial.print("Distance: ");
    Serial.println(currentDistance);

    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, LOW);

    if (currentDistance == 0 || currentDistance > 30) {
      digitalWrite(greenPin, HIGH);
    } else if (currentDistance > 15) {
      digitalWrite(yellowPin, HIGH);
    } else if (currentDistance > 5) {
      digitalWrite(redPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(30);
      digitalWrite(buzzerPin, LOW);
    } else {
      digitalWrite(redPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
    }
  }

  showNumber(currentDistance);
}
