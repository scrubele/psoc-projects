#include "lab.h"

//Змінні для зчитування значення з джойстика
int y = 0;
int x = 0;

//Ініціалізація компонент
void adc_validation_init(void){
    ADC_Start();
    ADC_StartConvert();
    PWM_X_Start();
    PWM_Y_Start();
}

//Алгоритм виконання завдання
void adc_get_led_position(void){
    //Зчитування аналогового сигналу за допомогою ADC(АЦП)
    x = ADC_GetResult16(0);
    y = ADC_GetResult16(1);   
    
    //Запис значення з ADC в PWM(ШІМ)
    //За допомогою PWM контролюється яркість діодів
    PWM_X_WriteCompare(x);
    PWM_Y_WriteCompare(y); 
}