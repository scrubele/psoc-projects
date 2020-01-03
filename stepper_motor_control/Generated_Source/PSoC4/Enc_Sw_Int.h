/*******************************************************************************
* File Name: Enc_Sw_Int.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Enc_Sw_Int_H)
#define CY_ISR_Enc_Sw_Int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Enc_Sw_Int_Start(void);
void Enc_Sw_Int_StartEx(cyisraddress address);
void Enc_Sw_Int_Stop(void);

CY_ISR_PROTO(Enc_Sw_Int_Interrupt);

void Enc_Sw_Int_SetVector(cyisraddress address);
cyisraddress Enc_Sw_Int_GetVector(void);

void Enc_Sw_Int_SetPriority(uint8 priority);
uint8 Enc_Sw_Int_GetPriority(void);

void Enc_Sw_Int_Enable(void);
uint8 Enc_Sw_Int_GetState(void);
void Enc_Sw_Int_Disable(void);

void Enc_Sw_Int_SetPending(void);
void Enc_Sw_Int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Enc_Sw_Int ISR. */
#define Enc_Sw_Int_INTC_VECTOR            ((reg32 *) Enc_Sw_Int__INTC_VECT)

/* Address of the Enc_Sw_Int ISR priority. */
#define Enc_Sw_Int_INTC_PRIOR             ((reg32 *) Enc_Sw_Int__INTC_PRIOR_REG)

/* Priority of the Enc_Sw_Int interrupt. */
#define Enc_Sw_Int_INTC_PRIOR_NUMBER      Enc_Sw_Int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Enc_Sw_Int interrupt. */
#define Enc_Sw_Int_INTC_SET_EN            ((reg32 *) Enc_Sw_Int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Enc_Sw_Int interrupt. */
#define Enc_Sw_Int_INTC_CLR_EN            ((reg32 *) Enc_Sw_Int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Enc_Sw_Int interrupt state to pending. */
#define Enc_Sw_Int_INTC_SET_PD            ((reg32 *) Enc_Sw_Int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Enc_Sw_Int interrupt. */
#define Enc_Sw_Int_INTC_CLR_PD            ((reg32 *) Enc_Sw_Int__INTC_CLR_PD_REG)



#endif /* CY_ISR_Enc_Sw_Int_H */


/* [] END OF FILE */
