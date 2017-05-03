# Use Arduino to control your turnouts, signals, and sensors with JMRI (and C/MRI)

Requires [Arduino CMRI](https://github.com/madleech/ArduinoCMRI)

# Install
* Copy/Paste `sketch_apr22a.pde` into the  Arduino IDE
* Install the `Arduino CMRI` package as a library
* Compile and install the software onto your Arduino
* Install sensor cables to the pins and add servos, lights, sensors, etc.
* Start PanelPro
* Configure C/MRI
* Add a node, node 0, all defaults
* Save
* Restart PanelPro
* After loading profile, wait about 10-15 seconds for it to connect
* Create/Load your panels
* Configure your layout in PanelPro

JMRIs System Name controls what pin to listen on. Arduino starts at pin 2 - JMRI starts at 1, so it can be confusing. Try matching up the pins to the JMRI table above and toggle them on/off to be certain you have the right pin.

# Qwerks
## Starting Panel Pro
Starting JMRI is a bit weird. Start PanelPro, select your profile then wait until you see the i/o lights flash or your servos kick on (10-15 seconds) then you can open your panels.

Failure to do so will result in no connection to your C/MRI.

## Disconnecting
If you disconnect or reset you'll need to restart PanelPro.

# Pin to JMRI
## Turnouts
* Pins: 2-18
* JMRI: CT1-17

## Toggles (LEDS/Lights/Signals/ETC)
* Pin 19-48
* JMRI: CT18-47


## Sensors
* Pins: A0-A15
* JMRI: CS1-15



# Parts List
I purchased the bulk of my parts with Amazon Same Day Shipping, the rest from eBay.

## Power
If you plan to run more then 12 pis you'll need a PSU
* [Coolmax 400W SATA&20/24pin Power Supply V-400](https://www.amazon.com/gp/product/B000BKBVT8/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B000BKBVT8&linkCode=as2&tag=nscaleard-20&linkId=cf775b619f49f44135df18b3dd96b744)

And if you want to keep it on while you unplug the usb (tho not required)
* [SainSmart 1A Power Supply Adapter 5.5x2.1mm Input 100V-240V For Arduino](https://www.amazon.com/gp/product/B00WW26JZE/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B00WW26JZE&linkCode=as2&tag=nscaleard-20&linkId=64cd31efc78159777c7b8c6de464a1ac)

## Servos
* [Sg90 Servo 9g Motor TowerPro RC Robot Helicopter Airplane Boat Controls(Pack of 10) by IFANCY-TECH](https://www.amazon.com/gp/product/B01G95KPZ4/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01G95KPZ4&linkCode=as2&tag=nscaleard-20&linkId=e70a3b7667552c12bddbadeb456a4fd2)

I mount the servos to the wood underside of my layout with servo tape
* [Racers Edge 1500 Narrow Servo Tape, 3/4](https://www.amazon.com/gp/product/B002PEB28I/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B002PEB28I&linkCode=as2&tag=nscaleard-20&linkId=312075f6034e052c5479f788bfd6f3c0)

## Arduino
Cheap nockoff, might want to spend more to get a better one
* [OSOYOO NEW ATmega2560-16AU CH340G MEGA 2560 R3 Board](https://www.amazon.com/gp/product/B00SFICZUM/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B00SFICZUM&linkCode=as2&tag=nscaleard-20&linkId=d2d0c427256ada272705ef8b78446abe)

Sensor sheild to easily hook up everything with servo cables
* [SainSmart MEGA Sensor Shield V2 for Arduino UNO MEGA1280 MEGA2560 MEGA2560 R3](https://www.amazon.com/gp/product/B007PABRNM/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B007PABRNM&linkCode=as2&tag=nscaleard-20&linkId=c6845803b299adb35251f95c3c73c753)

You're probablly better off with a servo wire kit, but I wanted Same Day Shipping, so I spliced a bunch of these together
* [DYWISHKEY 30cm Servo Cables, Male to Female (10 Pack)](https://www.amazon.com/gp/product/B01MXHLF3O/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01MXHLF3O&linkCode=as2&tag=nscaleard-20&linkId=3660814bdfbfaf11e7e14043f135142d)

## Block Detector
 * [OSOYOO 10PCS IR Infrared Obstacle Avoidance Sensor Module for Arduino Smart Car Robot](https://www.amazon.com/gp/product/B01I57HIJ0/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01I57HIJ0&linkCode=as2&tag=nscaleard-20&linkId=8796d3ca401af69ae40c0b9d52fe3572)

## Lights
* [20 pcs 1/4W 1% Metal Film Resistors](http://www.ebay.com/itm/361963578553?_trksid=p2057872.m2749.l2649&ssPageName=STRK%3AMEBIDX%3AIT)
* [10Pcs SMD Pre-Wired 0402 0603 0805 1206 LED Diodes White Red Light Soldered Line](http://www.ebay.com/itm/122032392862?_trksid=p2057872.m2749.l2649&var=421045039433&ssPageName=STRK%3AMEBIDX%3AIT) I used bi-color #603s.

 
