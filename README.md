Wireless Remote Controlled RedBot w/ XBee
========================================

<table class="table table-hover table-striped table-bordered">
  <tr align="center">
   <td><a href="https://learn.sparkfun.com/tutorials/wireless-joystick-hookup-guide/"><img src="https://cdn.sparkfun.com/assets/learn_tutorials/5/7/0/Joystick_Tutorial-01.jpg" alt="Wireless Joystick with SAMD21"></a></td>
   <td><a href="https://learn.sparkfun.com/tutorials/experiment-guide-for-redbot-with-shadow-chassis"><img src="https://cdn.sparkfun.com/assets/learn_tutorials/3/5/6/Redbot_Kit-93.jpg" alt=""></a></td>
  </tr>
  <tr align="center">
    <td><i>Wireless Remote</i></td>
    <td><i>Assembled RedBot</i></td>
  </tr>
</table>

Example code using the wireless remote controller (SAMD21) to control the SparkFun RedBot (ATmega328P) via XBee. A character is pipelined between two serial UARTs using a pair of XBee Series 1 Transcievers. Make sure to use software serial example code for the RedBot to avoid bricking your XBee. 

Repository Contents
-------------------

* **/A_Wireless_Joystick_Controller** - Example code for Controller (transmitting)
* **/B1_SW-Serial_Wireless_Controlled_RedBot** - Example code for RedBot (receiving) using the custom software serial library in the RedBot Library
* **/B2_HW-Serial_Wireless_Controlled_RedBot** - Example code for RedBot (receiving) using the hardware serial in the RedBot Library

Documentation
--------------

* **[Exploring XBees and XCTU: Configuring Networks](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu/#configuring-networks)** - Getting Started with XBees
* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.
* **[SAMD21 Mini/Dev Breakout Hookup Guide: Setting Up Arduino](https://learn.sparkfun.com/tutorials/samd21-minidev-breakout-hookup-guide/setting-up-arduino)** - Look here for SAMD21 board add-ons
* **[Wireless Joystick Hookup Guide](https://learn.sparkfun.com/tutorials/wireless-joystick-hookup-guide/)** - Basic hookup guide for the Wireless Joystick.  
* **[RedBot Assembly Guide](https://learn.sparkfun.com/tutorials/assembly-guide-for-redbot-with-shadow-chassis)** - Basic hookup guide for the RedBot.
* **[Experiment Guide](https://learn.sparkfun.com/tutorials/experiment-guide-for-redbot-with-shadow-chassis)** - Experiment guide for the RedBot.

XBee Series 1:  Point to Point Configuration
-------------------
[Digi Tutorial: XBee 802.15.4 (i.e. Wireless Serial)](https://www.digi.com/blog/basic-xbee-802-15-4-chat/)
  
* Master XBee (Transmitting, Controller)
  * CH = C
  * ID = 3333
  * DH = 0
  * DL = 2
  * MY = 1

* Slave XBee (Receiving, RedBot)
  * CH = C
  * ID = 3333
  * DH = 0
  * DL = 1 <- point to Master "MY"
  * MY = 2 <- Slave "MY", make it unique in the network.
  
License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
