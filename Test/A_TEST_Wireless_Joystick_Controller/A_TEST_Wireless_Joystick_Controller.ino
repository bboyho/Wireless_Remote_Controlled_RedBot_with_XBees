/* Wireless Joystick Controller Example
   Modified by: Ho Yun Bobby Chan
   Date: 1/18/19
   Written by: Alex Wende
   Date: 9/28/16
   SparkFun Electronics

   license: Creative Commons Attribution-ShareAlike 4.0 (CC BY-SA 4.0)
   Do whatever you'd like with this code, use it for any purpose.
   Please attribute and keep this license.

   This is example code for the Wireless Joystick to control a robot
   using XBee Series 1 on the same channel. Plug the first XBee into
   the Wireless Joystick board, and connect the second to the SparkFun RedBot Mainboard

   Pressing down on D2 (if you soldered the joystick on the right or a button) will check
   the joystick on the left. A character will be transmitted when moving the joystick:

     up = forward
     right = forward turn right
     down = reverse
     left = forward turn left

   The RedBot will need to be programmed to read those values.

   Connections to the motor driver is as follows:
   If you have not already, follow the RedBot Assembly Guide
   https://learn.sparkfun.com/tutorials/assembly-guide-for-redbot-with-shadow-chassis

   Power the motor driver with no higher than 9V!
*/

//#define L_TRIG 6        // Pin used for left trigger, not used...
//#define R_TRIG 3        // Pin used for right trigger, not used...
#define FORWARD_REVERSE_JOYSTICK A3   // Pin used for left joystick's y-component
#define TURN_JOYSTICK A2   // Pin used for left joystick x-component

int buttonACCELERATE_State; //value to store the state of the button press
#define ACCELERATE_BUTTON 2 // Pin used for right trigger

// We'll store the the analog joystick values here
int16_t forward_reverse_Stick_value;
int16_t turnStick_value;

char c_data;//send values through the serial monitor for debugging

#define ledPin = 13;      //LED indicator to tell when code has finished initializing
#define xbee_reset 12 //needed for certain XBee Series 3 modules

void setup() {

  //pinMode(L_TRIG, INPUT_PULLUP); // Enable pullup resistor for left trigger, not used
  //pinMode(R_TRIG, INPUT_PULLUP); // Enable pullup resistor for right trigger, not used

  SerialUSB.begin(9600);// Initialize Serial Monitor for DEBUGGING

  //Uncomment this if you want to wait until the serial monitor is open.
  //while (!SerialUSB); //Wait for Serial Monitor to Open

  SerialUSB.println("Wireless Joystick Controller Initialized");

  Serial1.begin(9600); // Start serial communication with XBee at 9600 baud
  SerialUSB.println("Wireless Joystick Controller's XBee Ready to Communicate");
  delay(10);

  pinMode(ACCELERATE_BUTTON, INPUT_PULLUP); // Enable pullup resistor for accelerate button D2

  /*power cycle XBee Series 3 by grounding RESET Pin to avoid dicontinuities in ramp up and brown out detection
  https://www.silabs.com/community/mcu/32-bit/knowledge-base.entry.html/2017/06/14/rmu_e203_avdd_ramp-j176
  Minimum Time to Force Reset:
  EFM32 devices = 50ns; EFM32PG/JG: Pearl and Jade Gecko =100ns
  https://www.silabs.com/community/mcu/32-bit/knowledge-base.entry.html/2016/07/22/minimum_reset_holdt-PglD
  */
  pinMode(xbee_reset, OUTPUT);
  digitalWrite(xbee_reset, HIGH);
  delayMicroseconds(1);
  digitalWrite(xbee_reset, LOW);
  delayMicroseconds(1);
  digitalWrite(xbee_reset, HIGH);

  //blink to show that we are done initializing
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
}

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
    SerialUSB.println("Sending character here ");
    SerialUSB.println(c_data);
  }



  if (buttonACCELERATE_State == LOW) {
    SerialUSB.println("Accelerate Button has been pressed!");

    if (forward_reverse_Stick_value > 1000) {
      SerialUSB.println("Forward");
      Serial1.print('A');//transmit to RedBot via XBees on the same channel
    }

    else if ( turnStick_value < 20) {
      SerialUSB.println("Turn Right");
      Serial1.print('B');
    }
    else if (forward_reverse_Stick_value < 20) {

      SerialUSB.println("Reverse");
      Serial1.print('C');
    }
    else if (turnStick_value > 1000) {

      SerialUSB.println("Turn Left");
      Serial1.print('D');
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
  }

  else {
    //delay(300);
  }


}
