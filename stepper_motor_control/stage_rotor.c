#include "lab.h"

void set_stage(int pin1, int pin2, int pin3, int pin4){
    Pin_1_Write(pin1);
    Pin_2_Write(pin2);
    Pin_3_Write(pin3);
    Pin_4_Write(pin4);  
}
void stage_1(void){
    set_stage(1,1,0,0);   
}

void stage_2(void){ 
    set_stage(0,1,0,0);
}

void stage_3(void){
    set_stage(0,1,1,0);
}

void stage_4(void){
    set_stage(0,0,1,0); 
}

void stage_5(void){
    set_stage(0,0,1,1);     
}

void stage_6(void){
    set_stage(0,0,0,1);    
}

void stage_7(void){
    set_stage(1,0,0,1);     
}

void stage_8(void){
    set_stage(1,0,0,0);  
}

void (*stage_list[])(void) = {stage_1,stage_2,stage_3,stage_4,
    stage_5,stage_6,stage_7,stage_8};