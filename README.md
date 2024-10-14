## super jumper

Automatically perform a super jump capable of obtaining the Super Suit by emulating a controller on an Arduino Micro


https://github.com/user-attachments/assets/6415ab1a-7826-4940-8d1e-5b9b829b21b6


### How to use

1. Make sure the "Auto Select" battle setting is set to "On".

2. Make sure the battle controls are "Type A".

3. Start a battle in mushroom way against a spikey enemy. Kill all enemies except a single spikey. 

4. On Mario's turn open the special menu and highlight "Super Jump" but don't press A on it. 

5. Plug the arduino micro directly into the Switch's USB-C port via a USB-Micro to USB-C cable.

6. Wait about 10 seconds for the jump sequence to initiate

Note that with the current code, there is only around a 10% chance that the super jump will successfully make it to 100. On my switch, it succeeds roughly 1 out of every 10 attempts. PRs welcome to try to get this more reliable! After I got the super suit I sort of lost motivation to keep improving it.

On your switch, the success rate might be slightly different - that's why you should initiate a battle against a Spikey, so you can have a tight retry loop. If it fails early, simply unplug the arduino, defend with the other 2 characters so that it is Mario's turn again, and repeat from step 4. If mario is consistently failing on a certain jump number, you can try adding or subtracting 10ms at a time from jump previous to the one it is failing on within `Joystick.c`. 

This has been tested with an OLED Switch running undocked. 

### Compiling and Flashing onto an Arduino Micro

You'll need the [Arduino IDE](https://www.arduino.cc/en/software) and AVR GCC toolchain installed. For AVR GCC, I recommend just pulling this pre-made docker image: https://hub.docker.com/r/lpodkalicki/avr-toolchain

LUFA has been included as a git submodule, so be sure to clone the repo like this:

```
git clone --recursive git@github.com:RPGillespie6/smrpg-super-jumper.git
```

Launch an avr toolchain docker container from the root of this repo with `docker run --rm -it -u 1000:1000 -v $PWD:/a -w /a --entrypoint sh lpodkalicki/avr-toolchain`, type `make`, and hit enter to compile. If all goes well, the printout in the terminal will let you know it finished the build:

```
avr-size   Joystick.elf
   text	   data	    bss	    dec	    hex	filename
   4366	   1484	     52	   5902	   170e	Joystick.elf
 [INFO]    : Finished building project "Joystick".
```

Now you'll need to flash the `Joystick.hex` to the arduino.

Start up Arduino IDE (you may need to start it as root). Under `File -> Preferences`, check `Show verbose output during: upload` and pick OK. With the Arduino plugged in and properly selected under `Tools`, upload any sketch. Find the line with `avrdude` and copy the entire avrdude command and all options into a terminal, replacing the .hex file and path to the location of the Joystick.hex created in the previous step. Also make sure the `-P/dev/??` port is the same as what Arduino IDE is currently reporting.

On my machine, the command looked like this:

```
"/root/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude" "-C/root/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega32u4 -cavr109 "-P/dev/ttyACM0" -b57600 -D "-Uflash:w:/home/user/smrpg-super-jumper/Joystick.hex:i"
```

Now double tap the reset button on the Arduino to put it into bootloader mode and run the `avrdude` command shortly there after. This may take several tries. You may need to press Enter first and then the reset button or try various timings. If it was successful you should see output similar to:

```
...

Writing | ################################################## | 100% 0.60s

avrdude: 5850 bytes of flash written

avrdude: safemode: lfuse reads as FF
avrdude: safemode: hfuse reads as D8
avrdude: safemode: efuse reads as CB
avrdude: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude done.  Thank you.
```

And that's it! Your super jumper is ready.

### Other Uses

The script found within `Joystick.c` can be modified and repurposed for all sorts of other tedious Mario RPG tasks, such as playing "Look The Other Way" to get the Star Egg, or farming rock candies from seaside town.

### Other Switch Automation Resources

- https://github.com/Brikwerk/nxbt (I tried to use this, and it worked well for non-time sensitive automation, but I couldn't get the timing tight enough for super jump)
- https://gist.github.com/bp2008/dff8957bfa040be51a2c561a2b2aca51 (this approach uses a physical servo to press the jump button. I didn't want to design a jig so I didn't go this route, but seems viable)
- https://www.consoletuner.com/products/titan-one/ (looks hackable with a scratch-like programming interface; see [this reddit thread](https://www.reddit.com/r/MarioRPG/comments/18nyaqq/i_coded_a_macro_that_will_automatically/))
- https://www.switch-up.ca/ (this also came up during my research but doesn't seem hackable)

### Thanks

Thanks to Bertrand Fan for his blog post on [Automating Zelda](https://medium.com/@bertrandom/automating-zelda-3b37127e24c8) as it provided the foundation on which to build this project (especially the nice little scripting system he created). 

Thanks to ZakKemble for the [millis](https://github.com/ZakKemble/millis) library he created, allowing access to a monotonic clock-esque abstraction with millisecond resolution.

Thanks to [Taric25](https://www.reddit.com/r/MarioRPG/comments/18nyaqq/i_coded_a_macro_that_will_automatically/) for providing some timing analysis of super jump on Reddit, which provided a good starting point for the timing of the jumps.

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).
