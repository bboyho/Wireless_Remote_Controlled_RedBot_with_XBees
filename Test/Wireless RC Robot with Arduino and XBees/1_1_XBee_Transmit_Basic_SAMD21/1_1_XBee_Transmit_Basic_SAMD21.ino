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

  //send commands via serial monitor for testing here
  if (SerialUSB.available()) {
    c_data = SerialUSB.read();//take character from serial monitor and store in variable

    Serial1.print(c_data);//send to XBee

    //echo back what was sent to serial monitor
    SerialUSB.println("Sending Character Here, ");
    SerialUSB.println(c_data);

    digitalWrite(status_LED, HIGH); //turn ON Status LED
    delayMicroseconds(500);//add short delay for LED for feedback, this can be commented out if it is affecting performance
  }

  digitalWrite(status_LED, LOW); //turn OFF Status LED

}//end loop

