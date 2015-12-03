//FILE NAME = LED_Patterns.h
// A Collection of functions to be called by the RTOS

void Pattern_Selector() {
    switch (autochange_pattern) {
        case 0:
            rtos_disable(Pattern_Selector);
            break;
        case 1:
            rtos_enable(Pattern_Selector);
            break;
        default:
            break;
    }
    if (autochange_pattern) {
        if ((current_pattern + 1) >= NUM_PATTERNS) {
            current_pattern = 0;
            Clear_Pattern_Positions();
        } else {
            current_pattern++;
            Clear_Pattern_Positions();
        }
        pattern_set = 0;
        //rtos_disable(Pattern_Selector);
    }
}

void Update_Pattern() {
    restart_wdt();
#ifdef DEBUG_SERIAL
    if (pattern_set == 0) {
        printf("Changing Pattern to %Lu\n\r", current_pattern);
    }
#endif

    switch (autochange_pattern) {
        case 0:
            rtos_disable(Pattern_Selector);
            break;
        case 1:
            rtos_enable(Pattern_Selector);
            break;
        default:
            break;
    }
    
    if (pattern_set == 0 || continue_pattern_calling == 1) {
        switch (current_pattern) {
            case 0: // All Red
                MakeAllRed();
                pattern_set = 1;
                continue_pattern_calling = 0;
                break;
            case 1: //All Green
                MakeAllGreen();
                pattern_set = 1;
                continue_pattern_calling = 0;
                break;
            case 2: //All Blue
                MakeAllBlue();
                pattern_set = 1;
                continue_pattern_calling = 0;
                break;
            case 3: //Slow Rainbow Fade on all Leds
                continue_pattern_calling = 1;
                All_Rainbow_Fade_200ms();
                pattern_set = 1;
                break;
            case 4:
                continue_pattern_calling = 1;
                Dot_Rainbow_Fade();
                pattern_set = 1;
                break;
            case 5:
                continue_pattern_calling = 1;
                All_Rainbow_Fade();
                pattern_set = 1;
                break;
            case 6:
                continue_pattern_calling = 1;
                Random_Chain();
                pattern_set = 1;
                break;
            case 7:
                continue_pattern_calling = 1;
                ShiftThreeColorThreeBlank(Color(255,0,0));
                pattern_set = 1;
                break;
            case 8:
                continue_pattern_calling = 1;
                ShiftThreeColorThreeBlank(Color(0,255,255));
                pattern_set = 1;
                break;
            case 9:
                continue_pattern_calling = 1;
                ShiftThreeColorThreeBlank(Wheel(rand()%767));
                pattern_set = 1;
                break;
            case 10:
                continue_pattern_calling = 1;
                ShiftOneColorOneBlank(Color(0,0,255));
                pattern_set = 1;
                break;
            case 11:
                continue_pattern_calling = 1;
                ShiftOneColorTwoBlank(Color(0,0,255));
                pattern_set = 1;
                break;
            case 12:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern1, Pattern1_Size);
                pattern_set = 1;
                break;
            case 13:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern2, Pattern2_Size);
                pattern_set = 1;
                break;
            case 14:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern3, Pattern3_Size);
                pattern_set = 1;
                break;
            case 15:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern4, Pattern4_Size);
                pattern_set = 1;
                break;
            case 16:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern5, Pattern5_Size);
                pattern_set = 1;
                break;
            case 17:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern6, Pattern6_Size);
                pattern_set = 1;
                break;
            case 18:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern7, Pattern7_Size);
                pattern_set = 1;
                break;
            case 19:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern8, Pattern8_Size);
                pattern_set = 1;
                break;
            case 20:
                continue_pattern_calling = 1;
                BMP_Play(&Pattern9, Pattern9_Size);
                pattern_set = 1;
                break;
            case 21: // All White for Tent Light
                MakeAllWhite();
                pattern_set = 1;
                continue_pattern_calling = 0;
                break;
        }
    }
}

void Button_Checker() {
    //check if any button is pressed
    if (button_status == 0) { //no buttons have been pressed

        //Power Button
        if (input(POWER_BUTTON_PIN) == 0) { //button is pressed
            bit_set(button_status, POWER_BUTTON_BIT);
            button_counter = 0;
        }

        //Up Button
        if (input(UP_BUTTON_PIN) == 0) { //button is pressed
            bit_set(button_status, UP_BUTTON_BIT);
            button_counter = 0;
        }

        //Down Button
        if (input(DOWN_BUTTON_PIN) == 0) { //button is pressed
            bit_set(button_status, DOWN_BUTTON_BIT);
            button_counter = 0;
        }

        //Left Button
        if (input(LEFT_BUTTON_PIN) == 0) { //button is pressed
            bit_set(button_status, LEFT_BUTTON_BIT);
            button_counter = 0;
        }      
        
        //Right Button
        if (input(RIGHT_BUTTON_PIN) == 0) { //button is pressed
            bit_set(button_status, RIGHT_BUTTON_BIT);
            button_counter = 0;
        }

        //Center Button
        if (input(CENTER_BUTTON_PIN) == 0) { //button is pressed
            bit_set(button_status, CENTER_BUTTON_BIT);
            button_counter = 0;
        }



    } else { //a button has been pressed, lets see if it's still pressed

        //Power Button
        if (bit_test(button_status, POWER_BUTTON_BIT)) {
            if (input(POWER_BUTTON_PIN) == 0) {
                button_counter++;
            } else {
                button_counter = 0;
                bit_clear(button_status, POWER_BUTTON_BIT);
            }
        }

        //Up Button
        if (bit_test(button_status, UP_BUTTON_BIT)) {
            if (input(UP_BUTTON_PIN) == 0) {
                button_counter++;
            } else {
                button_counter = 0;
                bit_clear(button_status, UP_BUTTON_BIT);
            }
        }

        //Down Button
        if (bit_test(button_status, DOWN_BUTTON_BIT)) {
            if (input(DOWN_BUTTON_PIN) == 0) {
                button_counter++;
            } else {
                button_counter = 0;
                bit_clear(button_status, DOWN_BUTTON_BIT);
            }
        }

        //Left Button
        if (bit_test(button_status, LEFT_BUTTON_BIT)) {
            if (input(LEFT_BUTTON_PIN) == 0) {
                button_counter++;
            } else {
                button_counter = 0;
                bit_clear(button_status, LEFT_BUTTON_BIT);
            }
        }

        //Right Button
        if (bit_test(button_status, RIGHT_BUTTON_BIT)) {
            if (input(RIGHT_BUTTON_PIN) == 0) {
                button_counter++;
            } else {
                button_counter = 0;
                bit_clear(button_status, RIGHT_BUTTON_BIT);
            }
        }

        //Center Button
        if (bit_test(button_status, CENTER_BUTTON_BIT)) {
            if (input(CENTER_BUTTON_PIN) == 0) {
                button_counter++;
            } else {
                button_counter = 0;
                bit_clear(button_status, CENTER_BUTTON_BIT);
            }
        }

    }

    if (button_counter > 5) {

        //Power Button
        if (bit_test(button_status, POWER_BUTTON_BIT)) {
            while (input(POWER_BUTTON_PIN) == 0) { //wait untill the button is released
                rtos_disable(Button_Checker);
            }
            rtos_enable(Button_Checker);
            Power_Button_Function();
            button_status = 0;
        }

        //Up Button
        if (bit_test(button_status, UP_BUTTON_BIT)) {
            while (input(UP_BUTTON_PIN) == 0) { //wait untill the button is released
                rtos_disable(Button_Checker);
            }
            rtos_enable(Button_Checker);
            Up_Button_Function();
            button_status = 0;
        }

        //Down Button
        if (bit_test(button_status, DOWN_BUTTON_BIT)) {
            while (input(DOWN_BUTTON_PIN) == 0) { //wait untill the button is released
                rtos_disable(Button_Checker);
            }
            rtos_enable(Button_Checker);
            Down_Button_Function();
            button_status = 0;
        }

        //Left Button
        if (bit_test(button_status, LEFT_BUTTON_BIT)) {
            while (input(LEFT_BUTTON_PIN) == 0) { //wait untill the button is released
                rtos_disable(Button_Checker);
            }
            rtos_enable(Button_Checker);
            Left_Button_Function();
            button_status = 0;
        }

        //Right Button
        if (bit_test(button_status, RIGHT_BUTTON_BIT)) {
            while (input(RIGHT_BUTTON_PIN) == 0) { //wait untill the button is released
                rtos_disable(Button_Checker);
            }
            rtos_enable(Button_Checker);
            Right_Button_Function();
            button_status = 0;
        }

        //Center Button
        if (bit_test(button_status, CENTER_BUTTON_BIT)) {
            while (input(CENTER_BUTTON_PIN) == 0) { //wait untill the button is released
                rtos_disable(Button_Checker);
            }
            rtos_enable(Button_Checker);
            Center_Button_Function();
            button_status = 0;
        }

    }
}
