//FILE NAME = Timer_Flags.c
// functions to avoid using delay calls

void Timer_Clear_Timer(int timer){
    if(timer < NUM_INTERNAL_TIMER){
        internal_timer[timer] = 0;
    }
}

void Timer_Clear_All_Timer(){
    int i;
    rtos_disable(Timer_Tic);
    for (i=0;i<NUM_INTERNAL_TIMER;i++){
        internal_timer[i] = 0;
    }
    rtos_enable(Timer_Tic);
}

int32 Timer_Get_Timer(int timer){
    if(timer < NUM_INTERNAL_TIMER){
        return internal_timer[timer];
    }else{
        return 0;
    }
}

void Timer_Tic(){
    //OUTPUT_HIGH(PIN_C4);
    int i;
    for (i=0;i<NUM_INTERNAL_TIMER;i++){
        internal_timer[i]++;
    }
    //OUTPUT_LOW(PIN_C4);
}

void Timer_Check() {
    int i;
    for (i = 0; i < NUM_INTERNAL_TIMER; i++) {
#ifdef DEBUG_SERIAL
        printf("Timer %i = %Lu\n\r",i,internal_timer[i]);
#endif
    }

}
