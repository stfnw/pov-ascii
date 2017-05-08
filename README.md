# pov-ascii

This is a simple demonstration of [persistence of vision (POV)](https://en.wikipedia.org/wiki/Persistence_of_vision) using the Atmel ATmega8 Microcontroller and eight LEDs to display ASCII-Strings.

I just wanted to try it out myself :-) (there are tons of projects like this online)

A few images of the final result:

[![project overview - plugged in](https://c1.staticflickr.com/5/4174/33672901443_ca79b36ae6_n.jpg)](https://www.flickr.com/photos/153997029@N03/33672901443/in/album-72157680361034923/ "project overview - plugged in") [![Hello World 2](https://c1.staticflickr.com/5/4185/34441671286_372e042dd7_n.jpg)](https://www.flickr.com/photos/153997029@N03/34441671286/in/album-72157680361034923/ "Hello World 2") [![Tinkering is fun](https://c1.staticflickr.com/5/4161/33640498514_beb979d4f8_n.jpg)](https://www.flickr.com/photos/153997029@N03/33640498514/in/album-72157680361034923/ "Tinkering is fun") [![Tinkering is fun convoluted 1](https://c1.staticflickr.com/5/4177/34441677486_986755f485_n.jpg)](https://www.flickr.com/photos/153997029@N03/34441677486/in/album-72157680361034923/ "Tinkering is fun convoluted 1")


## Origin / Sources

The idea and large parts of the code (including the Makefile) are mainly taken from Chapter 3, povToy.c of the book [Make: AVR Programming](http://shop.oreilly.com/product/0636920028161.do) by Elliot Williams, who made his source code publicly available on github: [AVR-Programming](https://github.com/hexagon5un/AVR-Programming).  
The source code was originally written for the ATmega 168, which is also used in the popular Arduino, so a few very small changes were necessary to port it to the ATmega8.
The fonts are not directly included (see below for details why)


## POV-Fonts

### How it works

POV works, because the eye does not react instantaniously to stimulus and therefore a small flash of light leaves a short afterimage and is perceived for a longer time than the light is actually turned on.
This optical illusion allows the drawing of seemingly floating shapes in the air, for example by turning leds on and off in a fast pattern and waving them around.


To display text, the different characters and symbols of the alphabet have to be translated to the corresponding blink-patterns for the LEDs.
In C, this is usually done by saving the needed characters in a two-dimensional array in a seperate header-file, where each inner array represents one character.


For example, to display the letter `A` with five LEDs (ignoring the other three bits of one byte), one could use the following pattern (where each `1` represents one turned-on LED and each `0` represents one turned-off LED)

```c
char A = {
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000110,
  0b00000101,
  0b00000110,
  0b00000100,
  0b00001000,
  0b00010000,
};
```

Written in hexadecimal this is a bit shorter, but unfortunately looks a bit more cryptic: `char A = { 0x10, 0x08, 0x04, 0x06, 0x05, 0x06, 0x04, 0x08, 0x1F }`

Without the `0`s the pattern itself looks like this: an `A` rotated by 90 degrees

    1
     1
      1
      11
      1 1
      11
      1
     1
    1


### Example fonts

The fonts used for this project are truncated to represent a subset of ASCII characters, more specificly the range from `0x20` (SPACE) to `0x7F` (DEL).
They are not directly included, because I am not sure under which license - if any - they were published.


However, here are a few example links where I took some fonts from:

 * https://www.mikrocontroller.net/topic/54860 ([direct link to zip](https://www.mikrocontroller.net/attachment/52208/font.zip))
 * https://github.com/radikalbytes/Arduino-POV-minimalist/blob/master/Arduino%20code/fonts.h
 * http://jared.geek.nz/2014/jan/custom-fonts-for-microcontrollers ([direct link to zip](http://jared.geek.nz/custom-fonts-for-microcontrollers/files/fonts.zip))


### Automatically generate the C-Array out of TrueType Fonts

Manually building and editing POV-fonts is a quite tedious and time-consuming task.
Fortunately there are ways to automate this and convert a TrueType font to a C-Array.

Usually this requires two steps:

 1. converting the TrueType font (a vector font) to a bitmap font or a series of black-and-white bitmaps for each character
    a general discussion of this step can for example be found here:

     * http://stackoverflow.com/questions/2672144/dump-characters-glyphs-from-truetype-font-ttf-into-bitmaps
     * http://stackoverflow.com/questions/17142331/convert-truetype-glyphs-to-png-image

    for a scripted approach of this step based on ImageMagick, see e.g. https://github.com/yukinoraru/ttf2png

 2. converting each bitmap to the corresponding C-Array by iterating over it pixel for pixel

During my search for a solution, I came across someone someone way smarter than me ([Jared Sanson](http://jared.geek.nz/2014/jan/custom-fonts-for-microcontrollers)), who already had taken a bit of his time and wrote [a small python script](http://jared.geek.nz/custom-fonts-for-microcontrollers/files/fonts.zip) based on the Python Imaging Library (PIL) to automate the whole process.
With a bit of parameter tweaking (e.g. the right settings for character height and width) and a [good pixel font](http://www.dafont.com/de/bitmap.php) as basis, the result can be quite remarkable.
