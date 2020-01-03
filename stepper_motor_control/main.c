#include "lab.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    algorithm_init();
    LCD_Start();
    encoder_start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {   
        switch_direction();
        algorithm_work_rotor();       
        //CyDelay(1000);
    }
}