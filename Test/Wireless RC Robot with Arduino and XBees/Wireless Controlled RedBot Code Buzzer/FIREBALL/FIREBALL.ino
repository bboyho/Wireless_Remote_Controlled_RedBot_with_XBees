/***********************************************************************
  SW-Serial Wireless Controlled RedBot
  Written by: Ho Yun Bobby Chan
  Date: 1/21/19
  SparkFun Electronics

  The first step to controlling the RedBot remotely is to first drive it
  from the Serial Monitor in a tethered setup. After uploading this sketch,
  keep the RedBot tethered to your computer with the USB cable. Flip the
  switches to the respective sides: MOTOR => RUN and POWER => ON. You
  will also need to have UART flipped to the XBee_SW_Serial side.

  Open up the Serial Monitor to send commands to the RedBot to move. This
  is useful for determining if the motors are wired correctly.

  A = forward
  B = forward turn right
  C = reverse
  D = forward turn left

  If your motors are not moving forward when you send the forward command,
  simply flip the wiring. You can adjust the code but that would require
  adjusting more than one line of code. This does not account for motor
  intensity like the example that is used with the Wireless Joystick Example
  and RedBot Experiment 9.

  If you have not already, follow the RedBot Assembly Guide
  https://learn.sparkfun.com/tutorials/assembly-guide-for-redbot-with-shadow-chassis

  Then insert the second XBee into RedBot mainboard. This assumes that you are
  using the software serial port so you will need to ensure that the switch
  for the XBee is flipped to the XBEE_SW_SERIAL side.

  WARNING: Make sure to flip the switch to the XBEE_SW_SERIAL when
  you are uploading to the RedBot Mainboard. You will have issues uploading
  code and possibly brick your XBee.

  This sketch was written by SparkFun Electronics, with lots of help from
  the Arduino community. This code is completely free for any use.

***********************************************************************/
#include "pitches.h" //include pitches.h from tab

#include <RedBot.h>  //include RedBot library
RedBotMotors motors; //make instance of RedBot
char data;  // variable for holding incoming data from XBee to Arduino

// We'll use RedBot SoftwareSerial to communicate with the XBee:
// For Atmega328P's
// XBee's DOUT (TX) is connected to pin 14 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 15 (Arduino's Software TX)
#include <RedBotSoftwareSerial.h>
RedBotSoftwareSerial RedBotXBee; //make instance of Software Serial, pins defined already in modified Software Serial Library

//LED to check if the LED is initialized.
const int status_LED = 13;

int coin_counter = 0;//counter for coins and 1-up

void setup(void)
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  RedBotXBee.begin(9600);// Initialize SW for XBee for receiving serial
  Serial.begin(9600);// Initialize HW for Serial Monitor for DEBUGGING

  //Status LED to see if the EL Sequencer is initializing
  for (int i = 0; i < 3; i++) {
    digitalWrite(status_LED, HIGH);//set Status LED on
    delay(50);
    digitalWrite(status_LED, LOW); //set Status LED off
    delay(50);
  }

  pinMode(9, OUTPUT); //buzzer

  //1-Up Sound
  tone(9, NOTE_E6, 125);
  delay(130);
  tone(9, NOTE_G6, 125);
  delay(130);
  tone(9, NOTE_E7, 125);
  delay(130);
  tone(9, NOTE_C7, 125);
  delay(130);
  tone(9, NOTE_D7, 125);
  delay(130);
  tone(9, NOTE_G7, 125);
  delay(125);
  noTone(9);

}

void loop(void)
{
  // if there is data coming in from XBee on Software Serial UART or Serial Monitor, do something with it.
  if (RedBotXBee.available() || Serial.available()) {
    if (RedBotXBee.available())
    {
      data = RedBotXBee.read();//store received value from XBee into variable
    }
    else if (Serial.available()) {
      data = Serial.read();//store received value from Serial Monitor into variable
    }

    Serial.println("Character Received, ");
    Serial.write(data);//send it out to serial monitor
    Serial.println();

    if (data == 'A') {
      Serial.println("Drive Forward");
      RedBotXBee.write('A');
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.drive(255); //forward
    }
    else if (data == 'B') {
      Serial.println("Turn Right");
      RedBotXBee.write('B');
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.leftMotor(-200); // Turn on left motor power (motorPower = )
      motors.rightMotor(100); // Turn on right motor power (motorPower = )
    }
    else if (data == 'C') {
      Serial.println("Reverse");
      RedBotXBee.write('C');
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.drive(-255); //reverse
    }
    else if (data == 'D') {
      Serial.println("Turn Left");
      RedBotXBee.write('D');
      digitalWrite(status_LED, HIGH); //turn ON Status LED

      motors.leftMotor(-100); // Turn on left motor power (motorPower = )
      motors.rightMotor(200); // Turn on right motor power (motorPower = )
    }
    else if (data == 'X') {
      // Play coin sound
      Serial.println("Coin Sound");


      if (coin_counter < 100) {
        coin_counter = coin_counter + 1; //add 1 coin
        Serial.print("Coin Counter = ");
        Serial.println(coin_counter);
        RedBotXBee.write('X');

        digitalWrite(status_LED, HIGH);  // turn the LED on
        tone(9, NOTE_B5, 100);
        delay(50);
        tone(9, NOTE_E6, 850);
        delay(400);
        noTone(9);
        digitalWrite(status_LED, LOW);  // turn the LED on
      }
      else if (coin_counter <= 100) {
        coin_counter = 0;//set back coins to 0;
        
        Serial.print("100 Coins Received! 1-Up");
        Serial.print("Coin Counter reset to = ");
        Serial.println(coin_counter);
        RedBotXBee.write('X');
        
        tone(9, NOTE_E6, 125);
        delay(130);
        tone(9, NOTE_G6, 125);
        delay(130);
        tone(9, NOTE_E7, 125);
        delay(130);
        tone(9, NOTE_C7, 125);
        delay(130);
        tone(9, NOTE_D7, 125);
        delay(130);
        tone(9, NOTE_G7, 125);
        delay(125);
        noTone(9);
      }
      digitalWrite(status_LED, HIGH); //turn ON Status LED

    }
    else if (data == 'Y') {
      // Play coin sound
      Serial.println("Fireball Sound");
      RedBotXBee.write('Y');

      // Play Fireball sound
      tone(9, NOTE_G4, 35);
      delay(35);
      tone(9, NOTE_G5, 35);
      delay(35);
      tone(9, NOTE_G6, 35);
      delay(35);
      noTone(9);
    }
    else {
      //nothing was received, do nothing
    }

    delay(100); // short pause so we are not constantly receiving characters
    motors.stop();//turn off motors
    digitalWrite(status_LED, LOW); //turn LOW Status LED
  }
}
