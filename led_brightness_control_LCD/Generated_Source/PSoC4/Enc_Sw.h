/*******************************************************************************
* File Name: Enc_Sw.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Enc_Sw_H) /* Pins Enc_Sw_H */
#define CY_PINS_Enc_Sw_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Enc_Sw_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Enc_Sw_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Enc_Sw_Read(void);
void    Enc_Sw_Write(uint8 value);
uint8   Enc_Sw_ReadDataReg(void);
#if defined(Enc_Sw__PC) || (CY_PSOC4_4200L) 
    void    Enc_Sw_SetDriveMode(uint8 mode);
#endif
void    Enc_Sw_SetInterruptMode(uint16 position, uint16 mode);
uint8   Enc_Sw_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Enc_Sw_Sleep(void); 
void Enc_Sw_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Enc_Sw__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Enc_Sw_DRIVE_MODE_BITS        (3)
    #define Enc_Sw_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Enc_Sw_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Enc_Sw_SetDriveMode() function.
         *  @{
         */
        #define Enc_Sw_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Enc_Sw_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Enc_Sw_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Enc_Sw_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Enc_Sw_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Enc_Sw_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Enc_Sw_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Enc_Sw_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Enc_Sw_MASK               Enc_Sw__MASK
#define Enc_Sw_SHIFT              Enc_Sw__SHIFT
#define Enc_Sw_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Enc_Sw_SetInterruptMode() function.
     *  @{
     */
        #define Enc_Sw_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Enc_Sw_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Enc_Sw_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Enc_Sw_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Enc_Sw__SIO)
    #define Enc_Sw_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Enc_Sw__PC) && (CY_PSOC4_4200L)
    #define Enc_Sw_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Enc_Sw_USBIO_DISABLE              ((uint32)(~Enc_Sw_USBIO_ENABLE))
    #define Enc_Sw_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Enc_Sw_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Enc_Sw_USBIO_ENTER_SLEEP          ((uint32)((1u << Enc_Sw_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Enc_Sw_USBIO_SUSPEND_DEL_SHIFT)))
    #define Enc_Sw_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Enc_Sw_USBIO_SUSPEND_SHIFT)))
    #define Enc_Sw_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Enc_Sw_USBIO_SUSPEND_DEL_SHIFT)))
    #define Enc_Sw_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Enc_Sw__PC)
    /* Port Configuration */
    #define Enc_Sw_PC                 (* (reg32 *) Enc_Sw__PC)
#endif
/* Pin State */
#define Enc_Sw_PS                     (* (reg32 *) Enc_Sw__PS)
/* Data Register */
#define Enc_Sw_DR                     (* (reg32 *) Enc_Sw__DR)
/* Input Buffer Disable Override */
#define Enc_Sw_INP_DIS                (* (reg32 *) Enc_Sw__PC2)

/* Interrupt configuration Registers */
#define Enc_Sw_INTCFG                 (* (reg32 *) Enc_Sw__INTCFG)
#define Enc_Sw_INTSTAT                (* (reg32 *) Enc_Sw__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Enc_Sw_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Enc_Sw__SIO)
    #define Enc_Sw_SIO_REG            (* (reg32 *) Enc_Sw__SIO)
#endif /* (Enc_Sw__SIO_CFG) */

/* USBIO registers */
#if !defined(Enc_Sw__PC) && (CY_PSOC4_4200L)
    #define Enc_Sw_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Enc_Sw_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Enc_Sw_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Enc_Sw_DRIVE_MODE_SHIFT       (0x00u)
#define Enc_Sw_DRIVE_MODE_MASK        (0x07u << Enc_Sw_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Enc_Sw_H */


/* [] END OF FILE */
