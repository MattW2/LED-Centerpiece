/*
  Note, parts of this code (addRandom function) were taken from Nathan Siedle's (sparkfun.com) excellent Arduino example for this strip. His code
  used some clever bit-banging to write to the strip. I prefer to use hardware SPI on a PIC, it seems to work very well for strips up to and
  beyond 5 meters.

  This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Consider supporting me by shopping in my store: http://www.insomnialighting.com

-Patrick Cantwell (3/1/2012)

*/

#include <stdlib.h>

#USE SPI (MASTER, SPI1, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)

#define LED_STRIP_LEN 160 // number of LEDs on the strip
#define RAND_MAX 255
unsigned int32 led_strip_colors[LED_STRIP_LEN];

void send_frame() {   // NOTE this strip takes data in BLUE, GREEN, RED order
  unsigned int16 i;
  unsigned int8 red,green,blue;
  
  for(i=0;i<LED_STRIP_LEN;i++) {
    blue = led_strip_colors[i] & 0xFF;
    green = (led_strip_colors[i] >> 8) & 0xFF;
    red = (led_strip_colors[i] >> 16) & 0xFF;
    spi_write(blue);
    spi_write(green);
    spi_write(red);
  }
  delay_us(500);    // delay 500us to latch the IC
}

void addRandom(void) { 
  unsigned int16 x;
  unsigned int32 new_color = 0;

  //First, shuffle all the current colors down one spot on the strip
  for(x = (LED_STRIP_LEN - 1) ; x > 0 ; x--)
    led_strip_colors[x] = led_strip_colors[x - 1];
    
  //Now form a new RGB color
  for(x = 0 ; x < 3 ; x++){
    new_color <<= 8;
    new_color |= rand(); //Give me a number from 0 to 0xFF
  }
  led_strip_colors[0] = new_color; //Add the new random color to the strip
}

void main()
{
    unsigned int16 i;

    for(i = 0 ; i < LED_STRIP_LEN ; i++) {led_strip_colors[i] = 0;}

    led_strip_colors[0] = 0xFF0000;  // red
    led_strip_colors[1] = 0x00FF00;  // green
    led_strip_colors[2] = 0x0000FF;  // blue
    led_strip_colors[3] = 0x00FFFF;  // green + blue
    led_strip_colors[4] = 0xFF00FF;  // red + blue
    led_strip_colors[5] = 0xFFFF00;  // red + green
    send_frame();

    delay_ms(5000);

    for(i=0;i<LED_STRIP_LEN;i++) {				// Let's be patriotic! (Red, White, Blue)
      if((i%3) == 0) {led_strip_colors[i] = 0xFF0000;}
      if((i%3) == 1) {led_strip_colors[i] = 0xFFFFFF;}
      if((i%3) == 2) {led_strip_colors[i] = 0x0000FF;}
    }
    send_frame();

    delay_ms(10000);

    for(i=0;i<LED_STRIP_LEN;i++) {				// Happy Saint Patrick's Day! (Green/White)
      if((i%2) == 0) {led_strip_colors[i] = 0x00FF00;}
      if((i%2) == 1) {led_strip_colors[i] = 0xFFFFFF;}
    }
    send_frame();
    
    delay_ms(10000);
    
    for(i=0;i<LED_STRIP_LEN;i++) {				// Let's go Yankees! (Blue/White)
      if((i%2) == 0) {led_strip_colors[i] = 0x0000FF;}
      if((i%2) == 1) {led_strip_colors[i] = 0xFFFFFF;}
    }
    send_frame();
    
    delay_ms(10000);

    for(i = 0 ; i < LED_STRIP_LEN ; i++) {led_strip_colors[i] = 0;}
    send_frame();
    
    while(true) {
      addRandom();
      send_frame();
    }
}

