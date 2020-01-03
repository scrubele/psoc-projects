/*******************************************************************************
* File Name: Rotor_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Rotor.h"

/* Check for removal by optimization */
#if !defined(Rotor_Sync_ctrl_reg__REMOVED)

static Rotor_BACKUP_STRUCT  Rotor_backup = {0u};

    
/*******************************************************************************
* Function Name: Rotor_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rotor_SaveConfig(void) 
{
    Rotor_backup.controlState = Rotor_Control;
}


/*******************************************************************************
* Function Name: Rotor_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Rotor_RestoreConfig(void) 
{
     Rotor_Control = Rotor_backup.controlState;
}


/*******************************************************************************
* Function Name: Rotor_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rotor_Sleep(void) 
{
    Rotor_SaveConfig();
}


/*******************************************************************************
* Function Name: Rotor_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Rotor_Wakeup(void)  
{
    Rotor_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
