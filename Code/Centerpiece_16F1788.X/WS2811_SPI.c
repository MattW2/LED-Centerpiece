//FILE NAME = WS2811_SPI.c
//File to output controls to a WS2811 led strip using PIC SPI commands

//needed Constant
//nDots - number of nodes in the chain

//needed Globel Vars
//node_list - 32bit array where all node colors are stored

//*****************Function List*****************//
//void send_frame(void)
	//Update the chain of WS2801 Nodes

//******************Functions*******************//

//use SPI to sent out all frames

#byte sspbuff=getenv("SFR:SSP1BUF")
#byte sspstat=getenv("SFR:SSP1STAT")
#bit ssp_has_data=sspstat.0
#define SPI_PUT(x) sspbuff=x

#define ws2811_zero 0b11110000
#define ws2811_one 0b11111110


//clear the sspbuffer
void ssp_clear_buff(void) {
   int8 dummy;
   dummy=sspbuff;
}

void wait_for_ssp(void) {
   while(!ssp_has_data);
   ssp_clear_buff(); //you must clear the buffer or overflow will trigger
}

/*
// Method 1 this won't work on a 32MHZ processor
void send_frame() {  //Test a singular bit, and then march the bits to the left..
  unsigned int16 i;
  unsigned int32 this_led;
  unsigned int bit;

  for(i=0;i<TDOTS;i++) {
    this_led = node_list[i];         // assign this LED's color to a throwaway variable
    for(bit=0;bit<24;bit++) {
      if(bit_test(this_led, 23)) {          // test fixed bit 23
        spi_write(ws2811_one);
      }
      else {
        spi_write(ws2811_zero);
      }                         
      this_led <<= 1;                       // march all the bits one position to the left so the 22nd bit is now in the 23rd position, etc..
    }
  }
  delay_us(50);                             // wait 50us to latch the string
}
 */


// Method 2 trying direct ssp write with buffer

void send_frame() {
    unsigned int16 i;
    //unsigned int32 this_led;
    int32 *this_led;
    unsigned int bit;

    int output;
    output = ws2811_zero;

    //ssp_clear_buff();

    this_led = &node_list[0];

    for (i = 0; i < TDOTS; i++) {
        
        if (bit_test(*this_led, 23)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 22)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 21)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 20)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 19)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 18)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 17)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 16)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 15)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 14)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 13)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 12)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 11)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 10)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 9)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 8)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);
        
        if (bit_test(*this_led, 7)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 6)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 5)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 4)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 3)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 2)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 1)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        if (bit_test(*this_led, 0)) {
            output = ws2811_one;
        } else {
            output = ws2811_zero;
        }
        SPI_PUT(output);

        this_led++;
    }
    delay_us(50); // wait 50us to latch the string
}