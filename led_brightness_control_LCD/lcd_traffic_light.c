#include "lab.h"
#include "stdio.h"

//Експорт зміних
extern uint8 sum_time1;
extern uint8 sum_time2;

//Масив чарів для запису в кожну стрічку LCD
static char buf1[17];
static char buf2[17];

extern volatile uint8 time;
extern volatile uint8 number_algorithm;
volatile uint8 status_set_color = 0; 

//Час кожного кольору
uint8 time_red = 0;
uint8 time_yellow = 0;
uint8 time_green = 0;

//Прототипи функцій
void lcd_time_color(void);
void lcd_set_red(void);
void lcd_set_yellow(void);
void lcd_set_green(void);
uint8 set_time(void);

//Кнопка енкодера яка встановлює екран ,такий який колір ми налаштовуєм
CY_ISR(Enc_Sw_Handler){
    status_set_color++;
    Enc_Sw_ClearInterrupt();
}

//Ініціалізація LCD перший вивід
void lcd_init(void){
    LCD_Start();
    LCD_ClearDisplay();
    sprintf(buf1,"Author");
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    //Тут виводиться імя автора лаболаторної
    sprintf(buf2," ");
    LCD_Position(1, 0);
    LCD_PrintString(buf2);
    CyDelay(6000);
}

//Ініціалізація енкодера
void enc_init(void){
    QuadDec_Start();
    QuadDec_WriteCounter(0);  
    Enc_Sw_Int_StartEx(Enc_Sw_Handler);
}

//Вивід першого екрану кольорів
//Під конжним кольор виводиться час світіння ,після налаштування цього часу
void lcd_time_color(void){
    LCD_ClearDisplay();
    sprintf(buf1,"Red Yellow Green");
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    //Виводиться тільки після нажаття кнопки переключення алгоритму. Кнопка розташована на мікроконтролері
    if(0 == number_algorithm){  
        if(time < time_red){
            sprintf(buf2,"%2d",time_red-time);
            LCD_Position(1, 0);
            LCD_PrintString(buf2);
        }else if(time_red <= time && time < sum_time1) {
            sprintf(buf2,"%6d",sum_time1-time);
            LCD_Position(1, 0);
            LCD_PrintString(buf2);
        }else if(sum_time1 <= time && time < sum_time2) {
            sprintf(buf2,"%13d",sum_time2-time);
            LCD_Position(1, 0);
            LCD_PrintString(buf2);
        }
    }
}

//Виводиться після першого нажаття на кнопку енкодера
//Через дрибіщання кнопки може перескакувати по меню і пропускати деякі назначення
void lcd_set_red(void){
    LCD_ClearDisplay();
    sprintf(buf1,"Set red time");
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    sprintf(buf2,"Time = %d",time_red);
    LCD_Position(1, 0);
    LCD_PrintString(buf2);
}

//Виводиться після третього нажаття на кнопку енкодера
void lcd_set_green(void){
    LCD_ClearDisplay();
    sprintf(buf1,"Set green time:");
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    sprintf(buf2,"Time = %d",time_green);
    LCD_Position(1, 0);
    LCD_PrintString(buf2);
}

//Виводиться після другого нажаття на кнопку енкодера
void lcd_set_yellow(void){
    LCD_ClearDisplay();
    sprintf(buf1,"Set yellow time:");
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    sprintf(buf2,"Time = %d",time_yellow);   
    LCD_Position(1, 0);
    LCD_PrintString(buf2);
}

//Алгорим повернення значення з енкодера ,який встановлює час світіння
uint8 set_time(void){
    uint8 value_encoder = 0;
    //Зчитування значення з енкодера
    value_encoder = QuadDec_ReadCounter();
    //Обмеження значень
    if(20 < value_encoder && 100 > value_encoder){
        value_encoder = 20;
        QuadDec_WriteCounter(20);
    }
    if(100 < value_encoder){
        value_encoder = 0;
        QuadDec_WriteCounter(0); 
    }    
    return value_encoder;
}

//Функція для визначення виводу екрану через нажаття кнопки енкодеру
//Також в функції відбувається призначення часу кожного кольору відповідно
void definition_set_color(void){
    if(0 == status_set_color){
        lcd_time_color();
    }else if(1 == status_set_color){
        time_red = set_time();
        lcd_set_red();
    }else if(2 == status_set_color){
        time_yellow = set_time();
        lcd_set_yellow();
    }else if(3 == status_set_color){
        time_green = set_time();
        lcd_set_green();
    }else{
        status_set_color = 0;
    } 
}