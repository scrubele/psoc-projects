#include "lab.h"

volatile uint8 time = 0;
volatile uint8 direction = 0;
volatile uint8 speed = 0;

uint8 value_PWM = 0;

uint8 set_pwm(void);

extern void(*stage_list[])();

const int ROTOR_STAGES_NUMBER = 8;
const int BACK_BUTTON = 2;
const int STOP_FORWARD_BUTTON = 1;
const int ADD_VALUE = 10;
const int SUBSTRACT_VALUE = 10;
const int MAX_SPEED_VALUE = 190;
const int MIN_SPEED_VALUE = 10;
const float MAX_ENCODER_VALUE = 10;
const float MIN_ENCODER_VALUE = 1;
const int MAX_SPEED = 2000;
char stage_rotor[8]={0b0011,0b0010,0b0110,0b0100,0b1100,0b1000,0b1001,0b0001};

CY_ISR(Timer_Handler){
    time++;
    if(ROTOR_STAGES_NUMBER == time){
            time = 0;
    }
    Timer_ClearInterrupt(Timer_INTR_MASK_TC);
}

CY_ISR(SW_1_Handler){
    direction = !direction;
    SW_1_ClearInterrupt();
}

CY_ISR(SW_2_Handler){
    direction = BACK_BUTTON;
    SW_2_ClearInterrupt();
}

CY_ISR(SW_3_Handler){
    if (speed >= MIN_SPEED_VALUE){
        speed -= SUBSTRACT_VALUE;
    } 
    SW_3_ClearInterrupt();
}

CY_ISR(SW_4_Handler){
    if (speed <= MAX_SPEED_VALUE){
        speed += ADD_VALUE;
    } 
    SW_4_ClearInterrupt();
}

void algorithm_init(void){
    Timer_Start();
    PWM_Start();
    Timer_Int_StartEx(Timer_Handler);
    SW_Int_1_StartEx(SW_1_Handler);
    SW_Int_2_StartEx(SW_2_Handler);
    SW_Int_3_StartEx(SW_3_Handler);
    SW_Int_4_StartEx(SW_4_Handler);
}

void encoder_start(void){
    QuadDec_Start();
    QuadDec_WriteCounter(0);
}

uint8 set_pwm(void){
    uint8 value_encoder = 0;
    value_encoder = QuadDec_ReadCounter();
    if (value_encoder > MAX_ENCODER_VALUE){
        value_encoder = MAX_ENCODER_VALUE;
    } else 
    if (value_encoder <MIN_ENCODER_VALUE){
        value_encoder = MIN_ENCODER_VALUE;   
    }  
    QuadDec_WriteCounter(value_encoder);
    return value_encoder;
}

void back_forward_movement(){
    if(speed || direction){
        Timer_WritePeriod(MAX_SPEED - (speed*10));
        switch(direction){            case 1:
                Rotor_Write(stage_rotor[ROTOR_STAGES_NUMBER-time]);
                break;
            case 2:
                Rotor_Write(stage_rotor[time]);
                break;
        }
    }
}

void algorithm_work_rotor(void){ 
    value_PWM = set_pwm()*10;
    PWM_WriteCompare(value_PWM);
    back_forward_movement();
}