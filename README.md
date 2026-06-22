# Kaiser Pet 
tamagotchi project for fallout summer 2026
created by Youna Son (≧∇≦)ﾉ

[ONSHAPE LINK](https://cad.onshape.com/documents/d6c669abeeb3d7413e8d21f8/w/bde522f027b95c0c69872acb/e/c43f71f52c280984713279bd?renderMode=0&uiState=6a3745600b13741097a9fee4)

_________

<img width="477" height="646" alt="image" src="https://github.com/user-attachments/assets/101170bf-15f9-4b65-97ee-135e2d80da55" />


# What is a Kaiser Pet? 

My custom themed tamagotchi has:
- RBG Screen
- Higher quality pixel art
- Photoresister (light sensor)

and most importantly... ITS FREAKING MICHAEL KAISER!!!

You take care of Kaiser from Blue Lock (animanga) like a standard tamagotchi. For example, you monitor their health, energy, and hunger levels and take care of them accordingly.

Hunger bar too low? 
Feed them!

Energy bar high?
Play with them!

Except it's better because you take care of the goat

______

# Why It Was Made? o((>ω< ))o

I cannot put into words for my love this character. The explanation behind it would likely take up 5 pages on a size 12, Times New Romans, single spaced google document for me to even START talking about it.
ps... you guys should see my embarassing pinterest page of over 300+ pins of Kaiser that made the zine process super easy (Sorry, I'm a pinterest warrior) AND my cosplays

Jokes aside, the main purpose is obviously: ENTERTAINMENT!

With the hype of the World Cup / FIFA, I think taking care of a character based off a soccer animanga would be super cool and fun.
Additionally, I really do want to use this regularly in my life, I love this character to the point where the whole event of fallout might've been an excuse to me building a super sick hardware project that suspiciously caters to my interests

# Pictures (☆▽☆)

CAD image:
<img width="618" height="654" alt="image" src="https://github.com/user-attachments/assets/abb18b34-bacf-405d-a8ad-1a965317a240" />



Render images (in the zine):

<img width="1142" height="1086" alt="image" src="https://github.com/user-attachments/assets/c6db2a83-76a5-4e23-b414-5b2028e46c5f" />


<img width="1314" height="938" alt="image" src="https://github.com/user-attachments/assets/ebc8d35b-e591-47a2-afcd-a8af6e7fbba6" />


PCB:


<img width="855" height="850" alt="image" src="https://github.com/user-attachments/assets/addebd3e-f9e8-495b-a79a-17b5af4984fc" />


<img width="1229" height="763" alt="image" src="https://github.com/user-attachments/assets/aed860b9-5d15-4c81-8f0c-69083dd2585f" />


Sneak peek of my pixel art!:

<img width="969" height="790" alt="image" src="https://github.com/user-attachments/assets/dca456a5-abc3-48f4-8869-5642c6115d39" />



______
Name,Qty,Unit,Price (USD),Total (USD),MOQ,MOQ Price,Source
Seeed Studio XIAO ESP32 C3,1,pcs,8.49,8.49,1,8.49,https://www.aliexpress.us/item/3256808047100037.html
1.77 inch TFT LCD 128x160 (HS180S10B),1,pcs,3.16,3.16,1,3.16,https://www.lcsc.com/product-detail/C5329585.html
Piezo Buzzer (1207-P6.5mm),1,pcs,0.50,0.50,10,5.02,https://www.aliexpress.us/item/3256810135642750.html
Tactile Buttons,3,pcs,0.23,0.69,10,2.25,https://www.aliexpress.us/item/3256807067168626.html
Photoresistor / LDR (LDR03),1,pcs,0.10,0.10,10,1.00,https://www.aliexpress.com
10k Ohm Resistor (R1),1,pcs,0.02,0.02,50,1.00,https://www.lcsc.com
Battery (BT1),1,pcs,5.16,5.16,1,5.16,https://www.aliexpress.us/item/3256808658204287.html
Battery Holder / Clip,1,pcs,0.30,0.30,5,1.50,https://www.aliexpress.com
2.54mm Pin Headers,1,pack,1.50,1.50,1,1.50,https://www.lcsc.com
M3 5mm Screws,5,pcs,0.04,0.20,50,1.92,https://www.aliexpress.us/item/2251832785290389.html
M3 10mm Screws,3,pcs,0.05,0.15,50,2.34,https://www.aliexpress.us/item/2251832785290389.html
M3 Threaded Standoffs,4,pcs,0.12,0.48,10,1.20,https://www.aliexpress.com
Custom PCB,1,pcs,0.40,0.40,5,2.00,https://jlcpcb.com
PLA 3D Printed Case,1,pcs,-,-,-,-,Self-Print / Local
Total,25,-,-,21.15,-,36.54,-


____
# BUILD & ASSEMBLY
___
# Required Tools
___
1) Solder
2) Sldering iron
3) Tweezers
4) 3D Printer
5) Screwdriver for M3 5mm & M3 10mm Screws
6) Electronic device to connect to tamagotchi through USB port

# Assembly Directions
____
1) Solder the Seeed Studio XIAO ESP32-C3, OLED display header connections, joystick module header connections, tact switches, battery connector, and all remaining through-hole and surface-mount components onto the PCB according to the schematic and PCB layout.
2) Inspect all solder joints for bridges, cold joints, or incomplete connections, then verify continuity on the power and ground nets using a multimeter.
3) Press-fit the custom button caps onto the tact switch actuators, ensuring each cap moves freely and returns to its neutral position without binding against the case.
4) Mount the joystick module to the PCB using 2× M2 × 5 mm screws, M2 standoffs, and M2 hex nuts, making sure the joystick remains centered and perpendicular to the PCB.
5) Route the battery leads through the designated cable path and place the lithium-polymer battery into the battery compartment located beneath the main PCB cavity in the bottom case.
6) Solder or connect the battery leads to the PCB battery connector, verifying correct polarity before powering the device.
7) Align the completed PCB assembly with the mounting posts inside the bottom case and carefully lower it into position, ensuring no wires become pinched between the PCB and enclosure.
8) Secure the PCB to the bottom case using 3× M3 mounting screws, tightening them evenly to avoid stressing the board.
9) Verify that the joystick stem and button caps properly align with their corresponding openings in the enclosure and move without obstruction.
10) Position the top case onto the bottom case, making sure all internal components remain seated correctly and all case edges are fully aligned.
11) Fasten the enclosure halves together using the specified M1.6 screws, tightening each screw gradually in an alternating pattern to ensure even clamping.
12) Install the required software libraries and board packages in the Arduino IDE, including the ESP32 board support package and any display or input libraries used by the firmware.
13) Connect the XIAO ESP32-C3 to a computer using a USB-C cable and select the correct board and COM port within the Arduino IDE.
14) Compile the firmware and resolve any compilation errors before proceeding with upload.
15) Upload the firmware to the ESP32-C3 and confirm that the upload process completes successfully.
16) Disconnect and reconnect power to verify that the device boots correctly without requiring a USB connection.
17) Test the OLED display by confirming that graphics, menus, and text render correctly with no missing pixels or display artifacts.
18) Test all button inputs and joystick directions, verifying that each input is correctly detected by the firmware and returns expected values.
19) Confirm battery-powered operation, charging functionality (if implemented), and overall device stability before final use.

Congrats! I hope someone can actually enjoy this and build it for themselves!


# CREDITS:
- ONSHAPE (for CAD)
- KiCAD (all hardware / PCB stuff)
- Fallout

LIBRARIES CREDITS
## Dependencies
This project requires the following Arduino libraries to be installed via the Library Manager:
* **Adafruit GFX Library** (by Adafruit)
* **Adafruit ST7735 and ST7789 Library** (by Adafruit)
* **SPI** (Built-in to Arduino IDE)

# PIXEL ART AND ZINE CREDITS
REFERENCES AND INSPIRATION (Pinterest!) :

- https://www.pinterest.com/pin/168322104817334436/
- https://www.pinterest.com/pin/888123989041302114/
- https://www.pinterest.com/pin/114560384269168373/
- https://www.pinterest.com/pin/888123989035366728/
- https://www.pinterest.com/pin/888123989035906915/
- https://pin.it/148EMhVAn
- https://share.google/kxDoDrVdniUi0Naia
- https://pin.it/6CnxexgHx

and obviously, kudos to Muneyuki Kaneshiro for making my favorite character and Yusuke Nomura for bringing him to life by drawing him.




