#include "lab.h"

//Функція ініціалізації яка викликається один раз для включення всіх компонент
void protocol_init(void){
    algorithm_init();
    lcd_init();
    enc_init();
}