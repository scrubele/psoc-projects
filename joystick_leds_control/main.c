#include "lab.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    protocol_init();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {   
        adc_get_led_position();
        lcd_degree();
    }
}

/* [] END OF FILE */
