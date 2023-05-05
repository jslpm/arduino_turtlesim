/* joystick_test.ino
 * For testing joystick values
 * 
 */

// Pin mapping
unsigned int buttonPin = 2;
unsigned int xPin = A0;
unsigned int yPin = A1;


// State variables
bool buttonState = 0;
unsigned int x = 0;
unsigned int y = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read data from joystick
  buttonState = digitalRead(buttonPin);
  x = analogRead(xPin);
  y = analogRead(yPin);

  // Show values to serial monitor
  Serial.print("button=");
  Serial.print(buttonState);
  Serial.print("  ");

  Serial.print("x=");
  Serial.print(x);
  Serial.print("  ");

  Serial.print("y=");
  Serial.println(y);

  delay(1);
}
