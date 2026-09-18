const bool COMMON_CATHODE = true;

// Segment pins: A, B, C, D, E, F, G, DP
const int segmentPins[8] = {29, 33, 25, 23, 22, 30, 26, 24};
// Digit pins: D1, D2, D3, D4
const int digitPins[4] = {28, 31, 32, 27};

const byte numbers[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int d = 0; d < 4; d++) {
    pinMode(digitPins[d], OUTPUT);
    digitOff(d);
  }
}

void setSegments(byte pattern) {
  for (int i = 0; i < 8; i++) {
    bool on = bitRead(pattern, i);
    if (!COMMON_CATHODE) on = !on;
    digitalWrite(segmentPins[i], on ? HIGH : LOW);
  }
}

void digitOn(int d) {
  digitalWrite(digitPins[d], COMMON_CATHODE ? LOW : HIGH);
}

void digitOff(int d) {
  digitalWrite(digitPins[d], COMMON_CATHODE ? HIGH : LOW);
}

void showNumber(int value) {
  int digits[4] = {
    (value / 1000) % 10,
    (value / 100) % 10,
    (value / 10) % 10,
    value % 10
  };

  for (int d = 0; d < 4; d++) {
    setSegments(numbers[digits[d]]);
    digitOn(d);
    delay(3);
    digitOff(d);
  }
}

void loop() {
  showNumber(1234);
}
