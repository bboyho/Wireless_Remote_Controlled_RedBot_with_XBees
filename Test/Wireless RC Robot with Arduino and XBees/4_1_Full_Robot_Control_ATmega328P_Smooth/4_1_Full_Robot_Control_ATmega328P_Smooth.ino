/* Full Robot Control ATmega328P Example Smooth
   Written by: Ho Yun Bobby Chan
   Date: 2/15/19
   SparkFun Electronics

   license: Creative Commons Attribution-ShareAlike 4.0 (CC BY-SA 4.0)
   Do whatever you'd like with this code, use it for any purpose.
   Please attribute and keep this license.

   The first step to controlling the RedBot remotely is to first drive it
   from the Serial Monitor in a tethered setup. This is example code
   for the RedBot Mainboard with ATmega328P. After uploading this sketch,
   keep the RedBot tethered to your computer with the USB cable. Flip the
   switches to the respective sides: MOTOR => RUN and POWER => ON. You
   will also need to have UART flipped to the XBee_SW_Serial side.

   Assuming that you have a pair of XBees 1s (or 3 configured with
   802.15.4 protocol) on the same channel, a character will be
   transmitted wirelessly between the XBees. Any charactered received
   from the XBee connected to the software serial defined pins will
   be passed to the Serial Monitor. For troubleshooting, any character
   sent through the Serial Monitor will be echoed back. Try testing the
   controller to see if the robot will move forward or sending the following
   character through the Serial Monitor.

       A = forward
       B = forward turn right
       C = reverse
       D = forward turn left
       J = coast
       K = stop

  If your motors are not moving forward when you send the forward command,
  simply flip the wiring. You can adjust the code but that would require
  adjusting more than one line of code. This does not account for motor
  intensity like the example that is used with the Wireless Joystick Example
  and RedBot Experiment 9.

  Code to smooth out control of XBee for faster response.

  WARNING: Make sure to flip the switch to the XBEE_SW_SERIAL when
  you are uploading to the RedBot Mainboard. You will have issues uploading
  code and possibly brick your XBee.
*/

#include <RedBot.h>  //include RedBot library
RedBotMotors motors; //make instance of RedBot

char c_data;  // variable for holding incoming data from XBee to Arduino

long counter = 0; //adding counter to prevent false triggers for a small period of time
boolean XBee_sent = false; //flag to see if we have received any characters after a certain period of time

// We'll use RedBot SoftwareSerial to communicate with the XBee:
// For Atmega328P's
// XBee's DOUT (TX) is connected to pin 14 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 15 (Arduino's Software TX)
#include <RedBotSoftwareSerial.h>
RedBotSoftwareSerial RedBotXBee; //make instance of Software Serial, pins     defined already in modified Software Serial Library

//LED to check if the LED is initialized.
const int status_LED = 13;

void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  RedBotXBee.begin(9600);// Initialize SW for XBee for receiving serial
  Serial.begin(9600);// Initialize HW for Serial Monitor for DEBUGGING

  //Status LED to see if the RedBot is initializing
  pinMode(status_LED, OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(status_LED, HIGH);//set Status LED on
    delay(50);
    digitalWrite(status_LED, LOW); //set Status LED off
    delay(50);
  }

  Serial.println("RedBot Initialized!");
}//end setup

void loop() {

  if (XBee_sent == false) {
    if (RedBotXBee.available() > 0 || Serial.available() > 0) {
      if (RedBotXBee.available()) {
        c_data = RedBotXBee.read();//store received value from XBee into variable
      }

      else if (Serial.available()) {
        c_data = Serial.read();//store received value from Serial Monitor into variable
      }

      counter = 0;
      XBee_sent = true;
      Serial.println("Character Received, ");
      Serial.write(c_data);//send it out to serial monitor
      Serial.println();
      digitalWrite(status_LED, HIGH); //turn ON Status LED
      //delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance

      if (c_data == 'A') {
        Serial.println("Drive Forward");
        RedBotXBee.write('A');
        digitalWrite(status_LED, HIGH); //turn ON Status LED

        motors.drive(255); //forward
      }
      else if (c_data == 'B') {
        Serial.println("Turn Right");
        RedBotXBee.write('B');
        digitalWrite(status_LED, HIGH); //turn ON Status LED

        motors.leftMotor(-200); // Turn on left motor power (motorPower = )
        motors.rightMotor(100); // Turn on right motor power (motorPower = )
      }
      else if (c_data == 'C') {
        Serial.println("Reverse");
        RedBotXBee.write('C');
        digitalWrite(status_LED, HIGH); //turn ON Status LED

        motors.drive(-255); //reverse
      }
      else if (c_data == 'D') {
        Serial.println("Turn Left");
        RedBotXBee.write('D');
        digitalWrite(status_LED, HIGH); //turn ON Status LED

        motors.leftMotor(-100); // Turn on left motor power (motorPower = )
        motors.rightMotor(200); // Turn on right motor power (motorPower = )
      }
      else if (c_data == 'J') {
        Serial.println("Coast");
        RedBotXBee.write('J');
        digitalWrite(status_LED, HIGH); //turn ON Status LED
        motors.coast();
      }
      else if (c_data == 'K') {
        Serial.println("Stop");
        RedBotXBee.write('K');
        digitalWrite(status_LED, HIGH); //turn ON Status LED
        motors.stop();
      }
    }
    else {
      motors.stop();//turn off motors if we do not receive a signal for a while
    }

  }

  if (counter >= 10) {//this section of code will reset the flag "XBee_Sent" so we can begin listening for characters again
    if (XBee_sent == true) {
      Serial.print("Counter = ");
      Serial.print(counter);
      Serial.println(", we are ready to receive characters again");
    }
    //delay(100); // short pause so we are not constantly receiving characters
    XBee_sent = false;
  }

  if (XBee_sent == true) {//this section of code is used as a delay to prevent false button presses
    counter = ++counter;//keep adding until we reach 10, then we can reset flag and begin receiving again

    //if connected to a computer, check to see the duration of the delay
    Serial.print("Counter = ");
    Serial.println(counter);

    c_data = RedBotXBee.read();//try to clear false triggers in buffer provided by Master XBee until counter resets
  }
  //delay(100); // short pause so we are not constantly receiving characters
  digitalWrite(status_LED, LOW); //turn OFF Status LED
}//end loop
