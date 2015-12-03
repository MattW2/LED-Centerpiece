/*
 * File:   Globals.h
 * Author: Matt Wasserman
 * Header file with all global vars and defines
 */

/* DEFINES FOR VERSION*/
//#define BOARD_V1_1
#define BOARD_V1_2 //and V1_3

#define WS2801
//#define WS2811

//#define DIRECT_LED
#define MOSFET_CONTROL_SHOE

/* DEFINES */
//#define TDOTS 46 // number of LEDs on the strip for tent light
//#define TDOTS 22 //standard womens belt
#define TDOTS 1 //Shealene Shoe's

#define NUM_INTERNAL_TIMER 1
#define NUM_PATTERN_POSITION 2
#define NUM_PATTERNS 22
#define DELAY_TIME_MS_JUMP 10
#define LED_ON_PIN PIN_A7
#define MAX_BRIGHTNESS 10
#define MIN_BRIGHTNESS 1

//defines for buttons
#define POWER_BUTTON_PIN PIN_A0
#define UP_BUTTON_PIN PIN_A1
#define DOWN_BUTTON_PIN PIN_A2
#define LEFT_BUTTON_PIN PIN_A3
#define RIGHT_BUTTON_PIN PIN_A4
#define CENTER_BUTTON_PIN PIN_A5
#define POWER_BUTTON_BIT 0
#define UP_BUTTON_BIT 1
#define DOWN_BUTTON_BIT 2
#define LEFT_BUTTON_BIT 3
#define RIGHT_BUTTON_BIT 4
#define CENTER_BUTTON_BIT 5

//Debug functions
#define DEBUG_SERIAL 1

struct rtos_stats {
   int32 task_total_ticks;       // number of ticks the task has used
   int16 task_min_ticks;         // the minimum number of ticks used
   int16 task_max_ticks;         // the maximum number of ticks ueed
   int16 hns_per_tick;           // us = (ticks*hns_per_tic)/10
};


/* GLOBAL VARIABLES*/
unsigned int32 node_list[TDOTS];
unsigned int32 internal_timer[NUM_INTERNAL_TIMER];
unsigned int16 pattern_position[NUM_PATTERN_POSITION]; //used to track current position within a patten
unsigned int16 current_pattern;
int1 pattern_set;
int1 continue_pattern_calling;
int1 led_power_status;
int16 timer_flags_counter;
unsigned int8 button_status;
unsigned int8 button_counter;
int autochange_pattern;
int16 delay_time_ms;
unsigned int8 brightness_value;


//BMP Patterns
unsigned int32 Pattern1[10] = {0xE05CFF, 0xCA53FF, 0xB44AFF, 0x9C40FF, 0x8637FF, 0x702EFF, 0x5A25FF, 0x421BFF, 0x2C12FF, 0x1609FF};
unsigned int32 Pattern2[10] = {0x0000FF, 0x00FF00, 0x0000FF, 0x00FF00, 0x0000FF, 0x00FF00, 0x0000FF, 0x00FF00, 0x0000FF, 0x00FF00};
unsigned int32 Pattern3[40] = {0x35FFFC, 0x38FCFA, 0x3BF9F8, 0x3EF5F6, 0x42F1F4, 0x46EDF1, 0x4AE8EE, 0x4FE3EB, 0x54DEE8, 0x59D8E5, 0x5ED2E1, 0x63CCDE, 0x69C6DA, 0x6FC0D6, 0x75B9D3, 0x7BB3CF, 0x81ACCB, 0x87A6C7, 0x8D9FC3, 0x9498BF, 0x9A91BB, 0xA08AB6, 0xA783B2, 0xAD7CAE, 0xB376AA, 0xB96FA6, 0xBF69A2, 0xC5629F, 0xCB5C9B, 0xD15697, 0xD65094, 0xDB4A90, 0xE0448D, 0xE53F8A, 0xEA3A87, 0xEE3584, 0xF23181, 0xF62D7F, 0xF9297D, 0xFC267B};
unsigned int32 Pattern4[60] = {0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFFFF4F, 0xFEFE50, 0xF4F457, 0xE7E760, 0xD8D86B, 0xC7C777, 0xB4B485, 0xA0A093, 0x8B8BA2, 0x7676B1, 0x6161C0, 0x4D4DCE, 0x3B3BDB, 0x2A2AE6, 0x1B1BF0, 0x0F0FF8, 0x0606FD, 0x0101FF, 0x0000FF, 0x0202FB, 0x0707F6, 0x0E0EEF, 0x1818E6, 0x2323DB, 0x3030CF, 0x3E3EC2, 0x4E4EB4, 0x5E5EA5, 0x6F6F96, 0x808087, 0x919177, 0xA2A268, 0xB3B35A, 0xC3C34C, 0xD1D13F, 0xDFDF33, 0xEBEB28, 0xF5F51F, 0xFDFD18, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16, 0xFFFF16};
//rainbow wave
unsigned int32 Pattern5[52] = {0x1021DE,0x4111EE,0x8511EE,0xC611EE,0xEA11E9,0xEE11C7,0xEE118E,0xEE1151,0xEE111C,0xEE1902,0xEE4200,0xEE8000,0xEEC000,0xEEF100,0xD9FF00,0xA1FF00,0x5BFF00,0x1DFF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x00FF00,0x1FFF00,0x61FF00,0xACFF00,0xE9FF00,0xFFF000,0xFFBB00,0xFF7700,0xFF3400,0xFF0902,0xFF001E,0xFF0057,0xFF0098,0xFF00D5,0xFB00FA,0xD400FF,0x8E00FF,0x4600FF,0x1200FF};
//white blue dot
unsigned int32 Pattern6[22] = {0xF9F9F9,0xF1F0F1,0xE4E2E5,0xF1EFF3,0x9E9CA2,0x1E1B20,0x1B1A1D,0x2C2C2D,0x626262,0xB3B3B3,0xF0EDF3,0xE6D9F3,0xA480C8,0x6F2DB3,0x660AC3,0x6503C8,0x5506A4,0x4A1B79,0x634F77,0x96909C,0xB2B1B4,0x9FA09F};
//Chase Green
unsigned int32 Pattern7[3] = {0xFF0000,0x000000,0x000000};
//Chase Red
unsigned int32 Pattern8[3] = {0x00FF00,0x000000,0x000000};
//Chase Blue
unsigned int32 Pattern9[3] = {0x0000FF,0x000000,0x000000};

unsigned int Pattern1_Size = 10;
unsigned int Pattern2_Size = 10;
unsigned int Pattern3_Size = 40;
unsigned int Pattern4_Size = 60;
unsigned int Pattern5_Size = 52;
unsigned int Pattern6_Size = 22;
unsigned int Pattern7_Size = 3;
unsigned int Pattern8_Size = 3;
unsigned int Pattern9_Size = 3;

