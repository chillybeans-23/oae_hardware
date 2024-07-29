# OAE Hardware

probe_tip branch includes probe nozzle PCB, as well as chassis CAD

## Bill of Materials

[TODO]
* Speakers
* Microphone
* 34AWG magnet wire
* 0402? components
* PCBs
* EEPROM chips
* HDMI cable
* Assorted heatshrink tubing
* 

## Assembly Instructions

The optimal location to assemble the probe is in the EE Proto Room. Here, you can find the necessary equipment to assemble the probe:

* Weller soldering station, with fine point iron tip
* Fine gauge lead-free solder wire
* No-clean flux
* Helping hands with silicone, with rubber alligator clip covers
* Silicone soldering pad
* Mounting putty (poster putty)
* Hotplate
* Tweezers
* Wire strippers
* Exacto knife
* Multimeter

### Step 1: Assemble the PCB

The nozzle PCB contains the Microchip 24LC32A I2C compatible serial EEPROM, its auxiliary components, and pads to solder HDMI and magnet wire to. To assemble the components before hand-soldering the magnet wire and HDMI cable, follow these instructions, and refer to Bradley Minch for use of his hotplate or expertise:

**Instructions for solder application**

[TODO] assemble another PCB and take pictures for each step

1. Lay PCB on silicone or other flat surface with IC/component side upwards
2. Lay stencil over PCB, ensuring the component pads line up
3. Carefully align stencil on top of PCB and hold down firmly
4. Applying tension, tape opposite corners of stencil to the work surface
5. Repeat for the other two corners of the stencil
6. Ensure the component pads still line up with the stencil cutouts, and the PCB is held securely in place
7. Mix the solder paste evenly
8. Apply a rice grain size amount of solder paste to the stencil next to the cutouts
9. Applying moderate pressure with the squeegee at a 30 degree angle with the surface, drag the solder paste along the stencil into the cutouts
10. Drag the solder paste the other way
11. Repeat 1-2 times until all the cutouts are full of solder paste
12. Using the squeegee, scrape the excess solder paste off the stencil
13. Scrape the excess solder paste off the squeegee back into the container
14. Untape the stencil from the work surface
15. Ensure there is an even layer of solder paste on the pads of the PCB
16. Using isopropyl alcohol and a Kimwipe, clean the squeegee and stencil

**Instructions for Populating the PCB**

1. Refer to the interactive Bill of Materials (BOM) for component values and locations [TODO]
2. Cut one 1uF capacitor and two 2k resistors off their respective tapes
3. Use angled tweezers to place the components
    * Getting one tweezer prong slightly sticky and just using that prong to place is better than pinching the components
    * Place hand on table close to PCB for stability
    * The specified capacitors and resistors have no polarity and can be placed with any side up, as long as the component lays flat along the PCB
