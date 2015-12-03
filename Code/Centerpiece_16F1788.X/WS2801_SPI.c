//FILE NAME = WS2801_SPI.c
//File to output controls to a WS2801 led strip using PIC SPI commands

//needed Constant
//nDots - number of nodes in the chain

//needed Globel Vars
//node_list - 32bit array where all node colors are stored

//*****************Function List*****************//
//void send_frame(void)
	//Update the chain of WS2801 Nodes
//******************Functions*******************//

//use SPI to sent out all frames
void send_frame(void) {   // NOTE this strip takes data in BLUE, GREEN, RED order


  unsigned int16 i;
  unsigned int16 red,green,blue;

  for(i=0;i<TDOTS;i++) {


#ifdef DIRECT_LED
    red = node_list[i] & 0xFF;
    green = (node_list[i] >> 8) & 0xFF;
    blue = (node_list[i] >> 16) & 0xFF;
    //apply brightness_control
    red = red * brightness_value / MAX_BRIGHTNESS;
    green = green * brightness_value / MAX_BRIGHTNESS;
    blue = blue * brightness_value / MAX_BRIGHTNESS;
#endif


#ifdef MOSFET_CONTROL_SHOE
    red = node_list[i] & 0xFF;
    green = (node_list[i] >> 8) & 0xFF;
    blue = (node_list[i] >> 16) & 0xFF;    
    red = 255 - (red * brightness_value / MAX_BRIGHTNESS);
    green = 255 - (green * brightness_value / MAX_BRIGHTNESS);
    blue = 255 - (blue * brightness_value / MAX_BRIGHTNESS);

#endif


    spi_write((int8)red);
    spi_write((int8)blue);
    spi_write((int8)green);
  }
  delay_us(500);    // delay 500us to latch the IC




}

