//FILE NAME = LED_Patterns.h
// A Collection of patterns to run using WS2801 leds using the RTOS system

void MakeAllRed(){
    MakeAllColor(Color(255,0,0));
}

void MakeAllGreen(){
    MakeAllColor(Color(0, 255, 0));
}

void MakeAllBlue(){
    MakeAllColor(Color(0, 0, 255));
}

void MakeAllWhite(){
    MakeAllColor(Color(255, 255, 255));
}

void All_Rainbow_Fade_200ms() {
    //Slow fade all colors      
    if (pattern_position[0] < 768) {
        if (Timer_Get_Timer(0) > 200) {
#ifdef DEBUG_SERIAL
            printf("Pattern Position = %Lu\n\r", pattern_position[0]);
#endif
            MakeAllColor(Wheel(pattern_position[0]));
            pattern_position[0]++;
            Timer_Clear_Timer(0);
        }
    } else {
        pattern_position[0] = 0;
    }
}

void Dot_Rainbow_Fade() {
    int16 i;
    int32 temp_color;
    // 3 cycles of all 768 colors in the wheel
    if (pattern_position[0] < 768) {
        if (Timer_Get_Timer(0) > delay_time_ms) {
#ifdef DEBUG_SERIAL
            printf("Pattern Position = %Lu\n\r", pattern_position[0]);
#endif
            for (i = 0; i < TDOTS; i++) {
                temp_color = Wheel(((i * 20) + (pattern_position[0] * 10)) % 768);
                node_list[i] = temp_color;
            }
            send_frame();
            pattern_position[0]++;
            Timer_Clear_Timer(0);
        }
    } else {
        pattern_position[0] = 0;
    }
}

void All_Rainbow_Fade() {
    //Slow fade all colors
    if (pattern_position[0] < 768) {
        if (Timer_Get_Timer(0) > delay_time_ms) {
#ifdef DEBUG_SERIAL
            printf("Pattern Position = %Lu\n\r", pattern_position[0]);
#endif
            MakeAllColor(Wheel(pattern_position[0]));
            pattern_position[0]++;
            Timer_Clear_Timer(0);
        }
    } else {
        pattern_position[0] = 0;
    }
}

void Random_Chain() {
    //Start with random colors then push random colors down
    if (Timer_Get_Timer(0) > delay_time_ms*2) {
        addRandom();
        send_frame();
        Timer_Clear_Timer(0);
    }
}

//push in 3 leds of color selected than shift it 1 led each time, 3 blanks
void ShiftThreeColorThreeBlank(int32 color_set) {
    if (Timer_Get_Timer(0) > delay_time_ms) {
        if (pattern_position[0] >= 6) {
            pattern_position[0] = 0;
        }
        if (pattern_position[0] % 6 < 3) {
            ShiftRight(color_set);
        } else {
            ShiftRight(color(0, 0, 0));
        }
        send_frame();
        pattern_position[0]++;
        Timer_Clear_Timer(0);
    }
}

//push in 1 leds of color selected than shift it 1 led each time, 1 blank
void ShiftOneColorOneBlank(int32 color_set) {
    if (Timer_Get_Timer(0) > delay_time_ms) {
        if (pattern_position[0] >= 2) {
            pattern_position[0] = 0;
        }
        if (pattern_position[0] % 2 < 1) {
            ShiftRight(color_set);
        } else {
            ShiftRight(color(0, 0, 0));
        }
        send_frame();
        pattern_position[0]++;
        Timer_Clear_Timer(0);
    }
}

//push in 1 leds of color selected than shift it 1 led each time, 1 blank
void ShiftOneColorTwoBlank(int32 color_set) {
    if (Timer_Get_Timer(0) > delay_time_ms) {
        if (pattern_position[0] >= 3) {
            pattern_position[0] = 0;
        }
        if (pattern_position[0] % 3 < 1) {
            ShiftRight(color_set);
        } else {
            ShiftRight(Color(0, 0, 0));
        }
        send_frame();
        pattern_position[0]++;
        Timer_Clear_Timer(0);
    }
}

/* work in progress
void Random_Color_Cross() {
//pattern_position[0] tracks the location of dot 1
//pattern_position[1] tracks the location of dot 2
    if (Timer_Get_Timer(0) > delay_time_ms) {
        if


    }

    RandomColor();

}
*/


void BMP_Play(int32 *PPattern, int Pattern_Size) {

    //pattern_position[0] is the location to pull the color information
    //pattern_position[1] tracks if we are moving up (0) or down (1)

    if (Timer_Get_Timer(0) > delay_time_ms) {
        //check if we are moving up and at the end upwards, if so turn around
        if (pattern_position[1] == 0 && pattern_position[0] + 1 >= Pattern_Size) {
            pattern_position[1] = 1;
            pattern_position[0]--;
        } else {
            //check if we are moving down and at the bottom
            if (pattern_position[1] == 1 && pattern_position[0] == 0) {
                pattern_position[1] = 0;
                pattern_position[0]++;
            } else {
                // see if we are just moving up
                if (pattern_position[1] == 0) {
                    pattern_position[0]++;
                } else {
                    //see if we are just moving down
                    if (pattern_position[1] == 1) {
                        pattern_position[0]--;
                    }
                }
            }
        }
        ShiftRight(*(PPattern + pattern_position[0]));
        #ifdef DEBUG_SERIAL
            printf("Pattern Position 0,1  = %Lu,%lu\n\r", pattern_position[0],pattern_position[1]);
        #endif
        send_frame();
        Timer_Clear_Timer(0);
    }
}


void Clear_Pattern_Positions() {
    int i;
    for (i = 0; i < NUM_PATTERN_POSITION; i++) {
        pattern_position[i] = 0;
    }
}

void Next_Pattern() {
    if ((current_pattern + 1) >= NUM_PATTERNS) {
        Clear_Pattern_Positions();
        current_pattern = 0;
    }else{
        Clear_Pattern_Positions();
        current_pattern++;
    }
    pattern_set = 0;
}

void Previous_Pattern() {
    if (current_pattern == 0){
        Clear_Pattern_Positions();
        current_pattern = NUM_PATTERNS - 1;
    }else{
        Clear_Pattern_Positions();
        current_pattern--;
    }
    pattern_set = 0;
}

void Speed_Up_Pattern() {
    if(delay_time_ms < 1000){
        delay_time_ms = delay_time_ms + DELAY_TIME_MS_JUMP;
    }
#ifdef DEBUG_SERIAL
    printf("Delay Time ms = %lu\n\r", delay_time_ms);
#endif
}

void Slow_Down_Pattern() {
    if(delay_time_ms > DELAY_TIME_MS_JUMP){
        delay_time_ms = delay_time_ms - DELAY_TIME_MS_JUMP;
    }
#ifdef DEBUG_SERIAL
    printf("Delay Time ms = %lu\n\r", delay_time_ms);
#endif
}

void Blink_Brightness() {
    int i;
    pattern_set = 1;
    continue_pattern_calling = 0;
    MakeAllColor(Color(0, 0, 0));
    delay_ms(100);
    for (i=0; i < brightness_value; i++){
        node_list[i] = Color(0,0,255);
    }
    send_frame();
    delay_ms(300);
    pattern_set = 0;
    continue_pattern_calling = 1;
}

void Increase_Brightness() {
    if (brightness_value < MAX_BRIGHTNESS){
        brightness_value++;
    }
    Blink_Brightness();
}

void Decrease_Brightness() {
    if (brightness_value > MIN_BRIGHTNESS){
        brightness_value--;
    }
    Blink_Brightness();
}




void Toggle_Autochange_Pattern() {
    if (autochange_pattern == 0) {
        //turn on the autochange pattern
        //blink green twice
        pattern_set = 1;
        continue_pattern_calling = 0;
        //make all green
        MakeAllColor(Color(0, 255, 0));
        delay_ms(500);
        MakeAllColor(Color(0, 0, 0));
        delay_ms(500);
        MakeAllColor(Color(0, 255, 0));
        delay_ms(500);
        MakeAllColor(Color(0, 0, 0));
        delay_ms(500);
        autochange_pattern = 1;
        pattern_set = 0;
        continue_pattern_calling = 1;
    } else {
        //red green twice
        pattern_set = 1;
        continue_pattern_calling = 0;
        //make all red
        MakeAllColor(Color(255, 0, 0));
        delay_ms(500);
        MakeAllColor(Color(0, 0, 0));
        delay_ms(500);
        MakeAllColor(Color(255, 0, 0));
        delay_ms(500);
        MakeAllColor(Color(0, 0, 0));
        delay_ms(500);
        autochange_pattern = 0;
        pattern_set = 0;
        continue_pattern_calling = 1;
    }
}


