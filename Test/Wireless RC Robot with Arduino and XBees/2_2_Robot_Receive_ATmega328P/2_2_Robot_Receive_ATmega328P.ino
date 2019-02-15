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

}//end setup

void loop() {

  if (RedBotXBee.available() || Serial.available()) {
    if (RedBotXBee.available()) {
      c_data = RedBotXBee.read();//store received value from XBee into variable

    }

    else if (Serial.available()) {
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
    else {
      //nothing was received, do nothing
    }


  }
  
  delay(100); // short pause so we are not constantly receiving characters
  motors.stop();//turn off motors
  digitalWrite(status_LED, LOW); //turn OFF Status LED
}//end loop
