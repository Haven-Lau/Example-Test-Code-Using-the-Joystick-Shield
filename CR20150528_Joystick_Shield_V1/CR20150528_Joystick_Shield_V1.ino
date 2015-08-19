// Store the Arduino pin associated with each input

// Select button is triggered when joystick is pressed
const byte PIN_BUTTON_SELECT = 8; 

const byte PIN_BUTTON_F = 7;
const byte PIN_BUTTON_E = 6;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 2;
const byte PIN_BUTTON_DOWN = 4;
const byte PIN_BUTTON_LEFT = 5;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUTTON_RIGHT, INPUT);
  digitalWrite(PIN_BUTTON_RIGHT, HIGH);

  pinMode(PIN_BUTTON_LEFT, INPUT);
  digitalWrite(PIN_BUTTON_LEFT, HIGH);

  pinMode(PIN_BUTTON_UP, INPUT);
  digitalWrite(PIN_BUTTON_UP, HIGH);

  pinMode(PIN_BUTTON_DOWN, INPUT);
  digitalWrite(PIN_BUTTON_DOWN, HIGH);

  pinMode(PIN_BUTTON_SELECT, INPUT);
  digitalWrite(PIN_BUTTON_SELECT, HIGH);
  
  pinMode(PIN_BUTTON_E, INPUT);
  digitalWrite(PIN_BUTTON_E, HIGH);
  
  pinMode(PIN_BUTTON_F, INPUT);
  digitalWrite(PIN_BUTTON_F, HIGH);
}

void loop() {
  
  Serial.print("U:");
  Serial.print(digitalRead(PIN_BUTTON_UP));
  Serial.print(" ");

  Serial.print("R:");
  Serial.print(digitalRead(PIN_BUTTON_RIGHT));
  Serial.print(" ");
  
  Serial.print("D:");
  Serial.print(digitalRead(PIN_BUTTON_DOWN));
  Serial.print(" ");
  
  Serial.print("L:");
  Serial.print(digitalRead(PIN_BUTTON_LEFT));
  Serial.print(" ");


  Serial.print("x:");
  Serial.print(analogRead(PIN_ANALOG_X));
  Serial.print(" ");

  Serial.print("y:");
  Serial.print(analogRead(PIN_ANALOG_Y));
  Serial.print(" ");


  Serial.print("S:");
  Serial.print(digitalRead(PIN_BUTTON_SELECT));
  Serial.print(" ");
  
  
  Serial.print("F:");
  Serial.print(digitalRead(PIN_BUTTON_F));
  Serial.print(" ");
  
  Serial.print("E:");
  Serial.print(digitalRead(PIN_BUTTON_E));
  Serial.print(" ");

  Serial.print("X+Y:");
  Serial.print(analogRead(PIN_ANALOG_X)*10000 + analogRead(PIN_ANALOG_Y));
  Serial.print(" ");

  Serial.println();
}
