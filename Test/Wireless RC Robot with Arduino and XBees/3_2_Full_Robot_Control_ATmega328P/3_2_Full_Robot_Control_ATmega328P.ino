#include "pitches.h" //include pitches.h from tab

#include <RedBot.h>  //include RedBot library
RedBotMotors motors; //make instance of RedBot

char c_data;  // variable for holding incoming data from XBee to Arduino

// We'll use RedBot SoftwareSerial to communicate with the XBee:
// For Atmega328P's
// XBee's DOUT (TX) is connected to pin 14 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 15 (Arduino's Software TX)
#include <RedBotSoftwareSerial.h>
RedBotSoftwareSerial RedBotXBee; //make instance of Software Serial, pins     defined already in modified Software Serial Library

//LED to check if the LED is initialized.
const int status_LED = 13;
int coin_counter = 0;//counter for coins and 1-up

void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  RedBotXBee.begin(9600);// Initialize SW for XBee for receiving serial
  Serial.begin(9600);// Initialize HW for Serial Monitor for DEBUGGING
  Serial.println("RedBot Initialized!");

  //Status LED to see if the RedBot is initializing
  pinMode(status_LED, OUTPUT);
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

}//end setup

void loop() {

  if (RedBotXBee.available() > 0 || Serial.available() > 0) {
    if (RedBotXBee.available() > 0) {
      c_data = RedBotXBee.read();//store received value from XBee into variable
    }

    else if (Serial.available() > 0) {
      c_data = Serial.read();//store received value from Serial Monitor into variable
    }

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
    else if (c_data == 'X') {
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
      }
      else if (coin_counter <= 100) {
        coin_counter = 0;//set back coins to 0;

        Serial.print("100 Coins Received! 1-Up");
        Serial.print("Coin Counter reset to = ");
        Serial.println(coin_counter);
        RedBotXBee.write('X');
        digitalWrite(status_LED, HIGH); //turn ON Status LED


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

    }
    else if (c_data == 'Y') {
      // Play coin sound
      Serial.println("Fireball Sound");
      RedBotXBee.write('Y');

      digitalWrite(status_LED, HIGH); //turn ON Status LED

      // Play Fireball sound
      tone(9, NOTE_G4, 35);
      delay(35);
      tone(9, NOTE_G5, 35);
      delay(35);
      tone(9, NOTE_G6, 35);
      delay(35);
      noTone(9);
    }
  }

  //delay(100); // short pause so we are not constantly receiving characters
  digitalWrite(status_LED, LOW); //turn OFF Status LED
}//end loop
