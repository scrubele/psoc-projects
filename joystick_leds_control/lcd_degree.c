#include "lab.h"
#include "stdio.h"

//Масив чарів для запису в кожну стрічку LCD
static char buf1[17];
static char buf2[17];

//Підтягування змінив з іншого файлу
extern int x;
extern int y;

//Ініціалізація LCD компоненти
void lcd_init(void){
    LCD_Start();
    LCD_ClearDisplay();
}

//Вивід значення зчитаних з ADC
void lcd_degree(void){
    LCD_ClearDisplay();
    sprintf(buf1,"Degrees");
    LCD_Position(0, 0);
    LCD_PrintString(buf1);
    sprintf(buf2,"x=%d y=%d",x,y);
    LCD_Position(1, 0);
    LCD_PrintString(buf2);
}