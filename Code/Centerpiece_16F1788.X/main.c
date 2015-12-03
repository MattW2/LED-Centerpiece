/* 
 * File:   main.c
 * Author: Matt Wasserman
 * Control Wedding LED Centerpieces
 *
 * Created on September 1, 2014, 5:54 PM
 */

#include <16F1788.h>
#fuses INTRC_IO, NOMCLR, NOBROWNOUT, WDT_NOSL, PUT
#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"

#USE DELAY(clock=32000000)

#use rs232(baud=57600, xmit=PIN_C6, rcv=PIN_C7, BITS=8, STOP=1, PARITY=N, INVERT)
#use rtos(timer=1)


/* TASK FUNCTIONS */
#task(rate=30s,max=5ms)
void Pattern_Selector();

#task(rate=10ms,max=5ms)
void Update_Pattern();

#task(rate=10ms,max=5ms)
void Button_Checker();

#task(rate=1ms,max=1ms)
void Timer_Tic();

/*
#task(rate=100ms,max=1ms)
void Timer_Check();
*/

/*Additonal Includes*/

#include "Timer_Flags.c"
#ifdef WS2801
    #include "WS2801_SPI.c"
#endif
#ifdef WS2811
    #include "WS2811_SPI.c"
#endif
#include "LED_Array.c"
#include "LED_Patterns.c"
#include "Buttons.c"
#include "RTOS_Functions.c"

/*MAIN FUNCTION*/
void main(int argc, char** argv) {
    //setup the IC
    setup_oscillator(OSC_8MHZ | OSC_PLL_ON); //32MHZ
    //set_tris_a(0b01111111);
    //set_tris_b(0b00000000);
    setup_wdt(WDT_16S);
    PORT_A_PULLUPS(0b01111111);
    PORT_B_PULLUPS(0b00000000);

#ifdef BOARD_V1_1
    #ifdef WS2801
        setup_spi(SPI_MASTER | SPI_CLK_DIV_16 | SPI_DO_B5 | SPI_SCK_B7 | SPI_SCK_IDLE_LOW | SPI_XMIT_L_TO_H);
    #endif
    #ifdef WS2811
        setup_spi(SPI_MASTER | SPI_CLK_DIV_4 | SPI_DO_B5 | SPI_SCK_B7 | SPI_L_TO_H | SPI_SCK_IDLE_LOW);
    #endif
#endif

#ifdef BOARD_V1_2
    #ifdef WS2801
        setup_spi(SPI_MASTER | SPI_CLK_DIV_16 | SPI_DO_C5 | SPI_SCK_C3 | SPI_SCK_IDLE_LOW | SPI_XMIT_L_TO_H);
    #endif
    #ifdef WS2811
        setup_spi(SPI_MASTER | SPI_CLK_DIV_4 | SPI_DO_C5 | SPI_SCK_C3 | SPI_L_TO_H | SPI_SCK_IDLE_LOW);
    #endif
#endif

    //turn on the leds
    OUTPUT_LOW(LED_ON_PIN);
    led_power_status = 1; //LED IS ON
    
    //clear the led_strup_colors variable
    setup();
    send_frame();
    delay_ms(100);

    //setup global variables
    autochange_pattern = 0;
    current_pattern = 5;
    //current_pattern = 21; //used for tent light
    button_status = 0;
    timer_flags_counter = 0;
    pattern_set = 0;
    continue_pattern_calling = 0;
    delay_time_ms = 1;
    Clear_Pattern_Positions();
    brightness_value = 10; //out of MAX_BRIGHTNESS
            

#ifdef DEBUG_SERIAL
    printf("System Started\n\r");
#endif

//Test code when checking LED programs
        //startup test of all colors
        //make all red
/*
        MakeAllColor(Color(255, 0, 0));
        delay_ms(1000);
        //make all green
        MakeAllColor(Color(0, 255, 0));
        delay_ms(1000);
        //make all blue
        MakeAllColor(Color(0, 0, 255));
        delay_ms(1000);

 */

    Timer_Clear_All_Timer();
            
#ifdef DEBUG_SERIAL
    printf("Starting RTOS\n\r");
#endif
    
    rtos_run();
}