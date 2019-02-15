#define FORWARD_REVERSE_JOYSTICK A3   // Pin used for left joystick's y-component
#define TURN_JOYSTICK A2   // Pin used for left joystick x-component

int buttonACCELERATE_State; //value to store the state of the button press
#define ACCELERATE_BUTTON 2 // Pin used for right trigger

// We'll store the the analog joystick values here
int16_t forward_reverse_Stick_value;
int16_t turnStick_value;

char c_data;//send values through the serial monitor for debugging

//LED to check if the LED is initialized.
const int status_LED = 13;

void setup() {

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

  //initialize variables to read buttons
  buttonACCELERATE_State = digitalRead(ACCELERATE_BUTTON);
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

  if (buttonACCELERATE_State == LOW) {
    SerialUSB.println("Accelerate Button has been pressed!");

    if (forward_reverse_Stick_value > 1000) {
      SerialUSB.println("Forward");
      Serial1.print('A');//transmit to RedBot via XBees on the same channel
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      //delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance
    }

    //Debug left analog joystick here
    //Boundaries vary depending on the joystick's read value
    //You may need to adjust the values in the condition statements to calibrate
    //Additional condition statements will need to be written for pivoting
    //and turning in reverse
    SerialUSB.print("forward_reverse_Stick_value  = "); //~1023 up, ~7-9 down
    delay(100);
    digitalWrite(status_LED, LOW); //turn OFF Status LED
  }
  else {
    //delay(300);
  }


}//end loop

