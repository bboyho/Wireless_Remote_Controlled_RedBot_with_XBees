Wireless Remote Controlled RedBot
========================================

Repository Contents
-------------------

* **/A_Wireless_Joystick_Controller** - Example code for Controller (transmitting)
* **/B_Wireless_Controlled_RedBot** - Example code for RedBot (receiving)

Documentation
--------------

* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.
* **[SAMD21 Mini/Dev Breakout Hookup Guide: Setting Up Arduino](https://learn.sparkfun.com/tutorials/samd21-minidev-breakout-hookup-guide/setting-up-arduino)** - Look here for SAMD21 board add-ons
* **[Wireless Joystick Hookup Guide](https://learn.sparkfun.com/tutorials/wireless-joystick-hookup-guide/)** - Basic hookup guide for the Wireless Joystick.  
* **[RedBot Assembly Guide](https://learn.sparkfun.com/tutorials/assembly-guide-for-redbot-with-shadow-chassis)** - Basic hookup guide for the RedBot.
* **[Experiment Guide](https://learn.sparkfun.com/tutorials/experiment-guide-for-redbot-with-shadow-chassis)** - Experiment guide for the RedBot.

XBee Series 1:  Point to Point Configuration
-------------------
* [Exploring XBees and XCTU: Configuring Networks](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu/#configuring-networks)
* [Digi Tutorial: XBee 802.15.4 (i.e. Wireless Serial)](https://www.digi.com/blog/basic-xbee-802-15-4-chat/)
  
  * Master XBee
  * CH = C
  * ID = 3333
  * DH = 0
  * DL = 2
  * MY = 1

* Slave XBee
  * CH = C
  * ID = 3333
  * DH = 0
  * DL = 1 <- point to Master "MY"
  * MY = 2 <- Slave "MY", make it unique in the network.
  
License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
