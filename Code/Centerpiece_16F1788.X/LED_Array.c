//FILE NAME = LED_Array.c
//Functions to generate 24bit colors patterns and manipulate them

//void addRandom(void)
	//shifts all dots one to the right and adds 1 random value

//int32 Color(int r, int g, int b)
	// Create a 24 bit color value from R,G,B

//int32 Wheel(int16 WheelPos){
	//Input a value 0 to 767 to get a color value.
	//The colours are a transition r - g -b - back to r

//void MakeAllColor(int32 color_set)
	//make all LEDS one color (overloaded function)

//void MakeAllColor(int red, int green, int blue)
	//make all LEDS one color, overloaded to accept red, green blue inputs

//void setup()
	////Clear out the array

//NOT IN THE FILE ANYMORE

//void ShiftRight(int16 newval)
	//Shift right, Shift the node_list one to the right
	//[i] -> [i+1]. Insert newval in node_list[0]

//void ShiftRight(int32 newval)
	//Shift right, Shift the node_list one to the right
	//[i] -> [i+1]. Insert newval in node_list[0]

void addRandom(void) {
  unsigned int16 x;
  unsigned int32 new_color = 0;

  //First, shuffle all the current colors down one spot on the strip
  for(x = (TDOTS - 1) ; x > 0 ; x--)
    node_list[x] = node_list[x - 1];

  //Now form a new RGB color
  for(x = 0 ; x < 3 ; x++){
    new_color <<= 8;
    new_color |= rand(); //Give me a number from 0 to 0xFF
  }
  node_list[0] = new_color; //Add the new random color to the strip
}

// Create a 24 bit color value from R,G,B
int32 Color(int r, int g, int b){
  //Take the lowest 8bits of each value and append them end to end
  	return( ((int32)(r & 0xFF)<<16) | ((int32)(g & 0xFF)<<8) | (int32)(b & 0xFF) );
}

//Input a value 0 to 767 to get a color value.
//The colours are a transition r - g -b - back to r
int32 Wheel(int16 WheelPos){
  int16 r;
  int16 g;
  int16 b;
  switch(WheelPos >> 8)  {
    case 0:
      r=255- WheelPos % 256;   //Red down
      g=WheelPos % 256;      // Green up
      b=0;                  //blue off
      break;
    case 1:
      g=255- WheelPos % 256;  //green down
      b=WheelPos % 256;      //blue up
      r=0;                  //red off
      break;
    case 2:
      b=255- WheelPos % 256;  //blue down
      r=WheelPos % 256;      //red up
      g=0;                  //green off
      break;
  }
  return(Color(r,g,b));
}

int32 RandomColor() {
    unsigned int16 x;
    unsigned int32 new_color;

    x = rand() % 767;
    new_color = Wheel(x);

    return new_color;
}


//make all LEDS one color (overloaded function)
void MakeAllColor(int32 color_set){
	int i;
	for(i=0; i<TDOTS; i++)
	{
            node_list[i] = color_set;
	}
	send_frame();
}

//make all LEDS one color, overloaded to accept red, green blue inputs
void MakeAllColor(int red, int green, int blue) {
	int i;
	for(i=0; i<TDOTS; i++)
	{
            node_list[i] = color(red, green, blue);
	}
	send_frame();
}

void setup() {
    int x;
    //Clear out the array
    for(x = 0; x < TDOTS ; x++){
        node_list[x] = 0;
    }
    send_frame();
}

void ShiftRight(int32 newval){
        int newPosition;
	for(newPosition = (TDOTS)-1; newPosition > 0; newPosition--) {
            node_list[newPosition] = node_list[newPosition - 1];
	}
	node_list[0] = newval; // fill the gap
}

void ShiftLeft(int32 newval){
        int newPosition;
	for(newPosition = 0; newPosition < (TDOTS - 1); newPosition++) {
            node_list[newPosition] = node_list[newPosition + 1];
	}
	node_list[TDOTS - 1] = newval; // fill the gap
}