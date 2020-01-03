/*******************************************************************************
* File Name: Enc_Sw.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Enc_Sw.h"

static Enc_Sw_BACKUP_STRUCT  Enc_Sw_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Enc_Sw_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Enc_Sw_SUT.c usage_Enc_Sw_Sleep_Wakeup
*******************************************************************************/
void Enc_Sw_Sleep(void)
{
    #if defined(Enc_Sw__PC)
        Enc_Sw_backup.pcState = Enc_Sw_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Enc_Sw_backup.usbState = Enc_Sw_CR1_REG;
            Enc_Sw_USB_POWER_REG |= Enc_Sw_USBIO_ENTER_SLEEP;
            Enc_Sw_CR1_REG &= Enc_Sw_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Enc_Sw__SIO)
        Enc_Sw_backup.sioState = Enc_Sw_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Enc_Sw_SIO_REG &= (uint32)(~Enc_Sw_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Enc_Sw_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Enc_Sw_Sleep() for an example usage.
*******************************************************************************/
void Enc_Sw_Wakeup(void)
{
    #if defined(Enc_Sw__PC)
        Enc_Sw_PC = Enc_Sw_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Enc_Sw_USB_POWER_REG &= Enc_Sw_USBIO_EXIT_SLEEP_PH1;
            Enc_Sw_CR1_REG = Enc_Sw_backup.usbState;
            Enc_Sw_USB_POWER_REG &= Enc_Sw_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Enc_Sw__SIO)
        Enc_Sw_SIO_REG = Enc_Sw_backup.sioState;
    #endif
}


/* [] END OF FILE */
