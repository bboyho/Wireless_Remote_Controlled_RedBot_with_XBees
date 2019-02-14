/***********************************************************************
  Wireless Controlled RedBot
  Written by: Ho Yun Bobby Chan
  Date: 1/18/19
  SparkFun Electronics

  The first step to controlling the RedBot remotely is to first drive it
  from the Serial Monitor in a tethered setup. After uploading this sketch,
  keep the RedBot tethered to your computer with the USB cable. Flip the
  switches to the respective sides: MOTOR => RUN and POWER => ON.

  Open up the Serial Monitor to send commands to the RedBot to move. This
  is useful for determining if the motors are wired correctly.

  A = forward
  B = forward turn right
  C = reverse
  D = forward turn left

  If your motors are not moving forward when you send the forward command,
  simply flip the wiring. You can adjust the code but that would require
  adjusting more than one line of code. This does not account for motor 
  intensity like the example that is used with the Wirless Joystick Example
  and RedBot Experiment 9.

  If you have not already, follow the RedBot Assembly Guide
  https://learn.sparkfun.com/tutorials/assembly-guide-for-redbot-with-shadow-chassis

  Then insert the second XBee into RedBot mainboard. This assumes that you are
  using the hardware serial port so you will need to ensure that the switch
  for the XBee is flipped to the XBEE_HW_SERIAL side.

  WARNING: Make sure to flip the switch to the XBEE_SW_SERIAL when
  you are uploading to the RedBot Mainboard. You will have issues uploading
  code and possibly brick your XBee.

  This sketch was written by SparkFun Electronics, with lots of help from
  the Arduino community. This code is completely free for any use.

***********************************************************************/

#include <RedBot.h>  //include library
RedBotMotors motors; //make instance of RedBot
char data;  // variable for holding incoming data from XBee to Arduino

//LED to check if the LED is initialized.
const int status_LED = 13;

void setup(void)
{
  Serial.begin(9600);// Initialize HW for Serial Monitor for DEBUGGING and receiving serial

  //Status LED to see if the EL Sequencer is initializing
  for (int i = 0; i < 3; i++) {
    digitalWrite(status_LED, HIGH);//set Status LED on
    delay(50);
    digitalWrite(status_LED, LOW); //set Status LED off
    delay(50);
  }

}

void loop(void)
{
  // if there is data coming in on the Serial Monitor, do something with it.
  if (Serial.available())  {
    data = Serial.read();//store received value into variable

    if (data == 'A') {
      Serial.println("Character Received, ");
      Serial.println("Drive Forward");
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.drive(255); //forward
    }
    else if (data == 'B') {
      Serial.println("Character Received, ");
      Serial.println("Turn Right");
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.leftMotor(-200); // Turn on left motor power (motorPower = )
      motors.rightMotor(100); // Turn on right motor power (motorPower = )
    }
    else if (data == 'C') {
      Serial.println("Character Received, ");
      Serial.println("Reverse");
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.drive(-255); //reverse
    }
    else if (data == 'D') {
      Serial.println("Character Received, ");
      Serial.println("Turn Left");
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.leftMotor(-100); // Turn on left motor power (motorPower = )
      motors.rightMotor(200); // Turn on right motor power (motorPower = )
    }
    else {
      //nothing was received, do nothing
    }

    delay(100); // short pause so we are not constantly receiving characters
    motors.stop();//turn off motors
    digitalWrite(status_LED, LOW); //turn LOW Status LED
  }
}

