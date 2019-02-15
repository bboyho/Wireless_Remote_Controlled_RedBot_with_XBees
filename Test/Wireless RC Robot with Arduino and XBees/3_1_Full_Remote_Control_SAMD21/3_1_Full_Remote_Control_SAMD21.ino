
#define L_TRIG 6        // Pin used for left trigger
#define R_TRIG 3        // Pin used for right trigger
boolean L_TRIGGER_State = HIGH;
boolean R_TRIGGER_State = HIGH;

#define FORWARD_REVERSE_JOYSTICK A3   // Pin used for left joystick's y-component
#define TURN_JOYSTICK A2   // Pin used for left joystick x-component

int prev_buttonACCELERATE_State;    //value to store the previous state of the button press
int current_buttonACCELERATE_State; //value to store the current state of the button press
#define ACCELERATE_BUTTON 2 // Pin used for right trigger

// We'll store the the analog joystick values here
int16_t forward_reverse_Stick_value;
int16_t turnStick_value;

char c_data;//send values through the serial monitor for debugging

//LED to check if the LED is initialized.
const int status_LED = 13;

void setup() {

  pinMode(L_TRIG, INPUT_PULLUP); // Enable pullup resistor for left trigger
  pinMode(R_TRIG, INPUT_PULLUP); // Enable pullup resistor for right trigger

  SerialUSB.begin(9600);// Initialize Serial Monitor for DEBUGGING

  //Uncomment this if you want to wait until the serial monitor is open.
  //while (!SerialUSB); //Wait for Serial Monitor to Open

  SerialUSB.println("Wireless Joystick Controller Initialized");

  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  SerialUSB.println("Wireless Joystick Controller's XBee Ready to Communicate");
  delay(10);

  pinMode(ACCELERATE_BUTTON, INPUT_PULLUP); // Enable pullup resistor for accelerate button D2

  //Status LED to see if the RedBot is initializing
  pinMode(status_LED, OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(status_LED, HIGH);//set Status LED on
    delay(50);
    digitalWrite(status_LED, LOW); //set Status LED off
    delay(50);
  }

}//end setup

void loop() {

  L_TRIGGER_State = digitalRead(L_TRIG);
  R_TRIGGER_State = digitalRead(R_TRIG);

  //initialize variables to read buttons
  current_buttonACCELERATE_State = digitalRead(ACCELERATE_BUTTON);
  /***button1state
    - LOW or 0 means pressed
    - HIGH or 1 means not pressed
   ****/
  //Store values read joystick
  forward_reverse_Stick_value = analogRead(FORWARD_REVERSE_JOYSTICK);
  turnStick_value = analogRead(TURN_JOYSTICK);

  //send commands via serial monitor for testing here
  if (SerialUSB.available()) {
    c_data = SerialUSB.read();//take character from serial monitor and store in variable

    Serial1.print(c_data);//send to XBee

    //echo back what was sent to serial monitor
    SerialUSB.println("Sending Character Here, ");
    SerialUSB.println(c_data);

  }

  if (current_buttonACCELERATE_State == LOW) {
    SerialUSB.println("Accelerate Button has been pressed!");

    if (forward_reverse_Stick_value > 1000) {
      SerialUSB.println("Forward");
      Serial1.print('A');//transmit to RedBot via XBees on the same channel
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      //delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance
    }
    else if ( turnStick_value < 20) {
      SerialUSB.println("Turn Right");
      Serial1.print('B');
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      //delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance
    }
    else if (forward_reverse_Stick_value < 20) {

      SerialUSB.println("Reverse");
      Serial1.print('C');
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      //delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance
    }
    else if (turnStick_value > 1000) {
      SerialUSB.println("Turn Left");
      Serial1.print('D');
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      //delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance

    }
    else {
      SerialUSB.println("Coast");
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      Serial1.print('J');
    }

    //Debug left analog joystick here
    //Boundaries vary depending on the joystick's read value
    //You may need to adjust the values in the condition statements to calibrate
    //Additional condition statements will need to be written for pivoting
    //and turning in reverse
    SerialUSB.print("forward_reverse_Stick_value  = "); //~1023 up, ~7-9 down
    SerialUSB.println(forward_reverse_Stick_value);
    SerialUSB.println("turnStick_value = "); //~1023 left, ~5-6 right
    SerialUSB.println(turnStick_value);
    delay(100);
    digitalWrite(status_LED, LOW); //turn OFF Status LED
  }
  else {//current_buttonACCELERATE_State == HIGH
    if (prev_buttonACCELERATE_State != current_buttonACCELERATE_State ) {
      SerialUSB.println("Stop");
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      Serial1.print('K');
    }
    digitalWrite(status_LED, LOW); //turn OFF Status LED
  }
  prev_buttonACCELERATE_State = current_buttonACCELERATE_State; //save current state

  if (L_TRIGGER_State == LOW) {
    SerialUSB.println("R Trigger Button has been pressed!");
    SerialUSB.println("Coin Sound");
    Serial1.print('X');
    digitalWrite(status_LED, HIGH); //turn ON Status LED

    delay(100);
    digitalWrite(status_LED, LOW); //turn OFF Status LED

  }
  if (R_TRIGGER_State == LOW) {
    SerialUSB.println("R Trigger Button has been pressed!");
    SerialUSB.println("Fireball Sound");
    Serial1.print('Y');
    digitalWrite(status_LED, HIGH); //turn ON Status LED

    delay(100);
    digitalWrite(status_LED, LOW); //turn OFF Status LED

  }

}//end loop
