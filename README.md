## super jumper

Automatically perform a super jump capable of obtaining the Super Suit by emulating a controller on an Arduino Micro

#### How to use

TBD

This repository has been tested using an Arduino Micro.

#### Compiling and Flashing onto an Arduino Micro

You'll need the [Arduino IDE](https://www.arduino.cc/en/software) and AVR GCC toolchain installed. For AVR GCC, I recommend just pulling this pre-made docker image: https://hub.docker.com/r/lpodkalicki/avr-toolchain

LUFA has been included as a git submodule, so cloning the repo like this:

```
git clone --recursive git@github.com:bertrandom/snowball-thrower.git
```

will put LUFA in the right directory.

Now you should be ready to rock. Launch an avr toolchain docker container with `docker run --rm -it -u 1000:1000 -v $PWD:/a -w /a --entrypoint sh lpodkalicki/avr-toolchain`, type `make`, and hit enter to compile. If all goes well, the printout in the terminal will let you know it finished the build.

#### Thanks

Thanks to Bertrand Fan for building on the Splatoon post printer [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) with a mini scripting engine.

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

Thanks to [exsilium](https://github.com/bertrandom/snowball-thrower/pull/1) for improving the command structure, optimizing the waiting times, and handling the failure scenarios. It can now run indefinitely!
