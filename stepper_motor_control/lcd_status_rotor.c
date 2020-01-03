#include "project.h"
#include "algorithm.h"
#include "stage_rotor.h"
#include "stdio.h"

static char buf1[17];
static char buf2[17];

extern uint8 direction;
extern uint8 speed;
extern uint8 value_PWM;

char str_stop[] = "Stop";
char str_forward[] = "Forward";
char str_back[] = "Back";

void lcd_show_rotor_direction(char str[]){
    LCD_ClearDisplay();
    sprintf(buf1,"%s PWM=%d v",str,value_PWM);
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    sprintf(buf2,"Speed=%d",speed);
    LCD_Position(1, 0);
    LCD_PrintString(buf2); 
    
}

void switch_direction(void){
    switch(direction){
        case 0:
            lcd_show_rotor_direction(str_stop);
            break;
        case 1: 
            lcd_show_rotor_direction(str_forward);
            break;
        case 2:
            lcd_show_rotor_direction(str_back);
            break;
    }
}