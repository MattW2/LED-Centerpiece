//FILE NAME = Buttons.h
//Functions to deal with buttons being pressed

void Power_Button_Function() {
    if (led_power_status == 0) { //turning on
#ifdef DEBUG_SERIAL
        printf("Turning on Power to LEDs\n\r");
#endif
        OUTPUT_LOW(LED_ON_PIN);
        led_power_status = 1; //LED IS ON
        delay_us(100);
        send_frame();
    } else { //turning off
        OUTPUT_HIGH(LED_ON_PIN);
        led_power_status = 0; //LEDS are off
        disable_interrupts(GLOBAL);

        clear_interrupt(INT_IOC_A0_L2H);
        delay_us(200);
        enable_interrupts(INT_IOC_A0_L2H);

#ifdef DEBUG_SERIAL
        printf("Going to Sleep\n\r");
#endif
        sleep();

        restart_wdt();
#ifdef DEBUG_SERIAL
        printf("Wake Up\n\r");
#endif

        delay_cycles(1);
        disable_interrupts(INT_IOC_A0_L2H);
        
        rtos_disable(Button_Checker);
        OUTPUT_LOW(LED_ON_PIN);
        led_power_status = 1; //LED IS ON
        delay_ms(50);
        send_frame();
        delay_ms(300);
        rtos_enable(Button_Checker);
    }
}

void Up_Button_Function() {
    Next_Pattern();
}

void Down_Button_Function() {
    Previous_Pattern();
}

void Left_Button_Function() {
    switch (autochange_pattern) {
        case 0:
            Speed_Up_Pattern();
            break;
        case 1:
            Increase_Brightness();
            break;
        default:
            break;
    }
}

void Right_Button_Function() {
    switch (autochange_pattern) {
        case 0:
            Slow_Down_Pattern();
            break;
        case 1:
            Decrease_Brightness();
            break;
        default:
            break;
    }
}

void Center_Button_Function() {
    Toggle_Autochange_Pattern();
}




