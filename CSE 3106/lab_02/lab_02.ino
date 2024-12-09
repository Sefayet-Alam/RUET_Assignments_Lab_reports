const int LED = PB0;
// The LED is connected to pin 9
const int BUTTON = PB15;
// The Button is connected to pin 2
void setup() {
  pinMode(LED, OUTPUT);
  // Set the LED pin as an output
  pinMode(BUTTON, INPUT);
  // Set button as input (not required)
}
void loop() {
  
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
}
