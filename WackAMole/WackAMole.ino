// Fields
// Joystick variables
const int sX = A3;  // Analog input #4, x axis
const int sY = A4;  // Analog input #5, y axis
int sSX;            // State of x, read from sX
int sSY;            // State of y, read from sY
int sS;             // This is for conversition of analog

// Game Variables
int rNum;           // RNG int that choosing the random light

// Difficulty constants, three should be a good number
// Also, Expert isn't divided in half of hard, since it makes it almost impossible to put in the correct guess
//  That's why it's set at 350 to ensure it's fair
const int easy = 1000;
const int hard = 500;
const int expert = 350;

// LEDs
int ledPins[] = {7, 8, 9, 10, 11, 12}; // Where the pins get their power from
int pinCount = 6;                         // How many pins I have in total

// Button Variables
int btnClick = 0;

void setup() {
  // put your setup code here, to run once:

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  
  Serial.begin(9600);

  // Get the input of the joystick, hopefully this works!
  pinMode(sX, INPUT);
  pinMode(sY, INPUT);

  // Assigning the pins as outputs - done easily with a for loop
  for (int i = 0; i < pinCount; i++) {
    pinMode(i + pinCount + 1, OUTPUT);
  }

  //pinMode(12, OUTPUT);

  // Button
  pinMode(2, INPUT_PULLUP);
}

void loop() {

  // Was used for testing to make sure leds were working!
  /*
  for(int i = 0; i < pinCount; i++) {
    digitalWrite(i + pinCount + 1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(i + pinCount + 1, LOW);    // turn the LED off by making the voltage LOW
    delay(1000); 
  }*/
  // Buttons
  int buttonVal = digitalRead(2);
  Serial.println(buttonVal);

  // Add a number to the counter when button is pushed down
  if (buttonVal == 0) {
    btnClick = btnClick + 1;
    delay(250);
  }

  if(btnClick == 3) {
    btnClick = 0;
  }
  
  // put your main code here, to run repeatedly:
  rNum = random(4);                   // Get a random number
  delay(1000);
  digitalWrite(ledPins[rNum], HIGH);  // Light the randomly chosen bulb

  // Checks the button counter and what value it holds
  if(btnClick == 0) {
    delay(easy);
    Serial.println("Easy");
  }

  if(btnClick == 1) {
    delay(hard);
    Serial.println("Hard");
  }

  if(btnClick == 2) {
    delay(expert);
    Serial.println("Expert");
  }
  
  // Joysticks!
  sSX = analogRead(sX); // Read x axis input
  Serial.print("sX = ");
  
  Serial.println(sSX);
  sSY = analogRead(sY); // Read y axis input
  Serial.print("sY = ");
  Serial.println(sSY);

  // Convert the x and y inputs!
  //  Basically, there are 4 possibilites - Left, Right, Up, and Down
  sS = 0;

  // Switch case is most efficent here
  // Note: I'm not 
  switch(sSX) {
    case 0:
      sS = 1; // Down
      break;
    case 1023:
      sS = 2; // Up
      break;
  }

  switch(sSY) {
    case 0:
      sS = 3; // Left
      break;
    case 1023:
      sS = 4; // Right
      break;
  }

  digitalWrite(ledPins[rNum], LOW);

  // Check the user input!
  // This should be indicating correct choice - Green Light
  if(sS - 1 == rNum) {
    for (int k = 0; k <= 3; k++) {
      digitalWrite(ledPins[4], HIGH);
      delay(50);
      digitalWrite(ledPins[4], LOW);
      delay(50);
    }
  }
  else {
    for (int i=0; i<=3; i++) {       // Blinking red light indicates incorrect choice
      digitalWrite(ledPins[5], HIGH);
      delay(50);
      digitalWrite(ledPins[5], LOW);
      delay(50);
    }
  }
}
