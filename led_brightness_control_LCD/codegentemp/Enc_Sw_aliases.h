/*******************************************************************************
* File Name: Enc_Sw.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Enc_Sw_ALIASES_H) /* Pins Enc_Sw_ALIASES_H */
#define CY_PINS_Enc_Sw_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Enc_Sw_0			(Enc_Sw__0__PC)
#define Enc_Sw_0_PS		(Enc_Sw__0__PS)
#define Enc_Sw_0_PC		(Enc_Sw__0__PC)
#define Enc_Sw_0_DR		(Enc_Sw__0__DR)
#define Enc_Sw_0_SHIFT	(Enc_Sw__0__SHIFT)
#define Enc_Sw_0_INTR	((uint16)((uint16)0x0003u << (Enc_Sw__0__SHIFT*2u)))

#define Enc_Sw_INTR_ALL	 ((uint16)(Enc_Sw_0_INTR))


#endif /* End Pins Enc_Sw_ALIASES_H */


/* [] END OF FILE */
