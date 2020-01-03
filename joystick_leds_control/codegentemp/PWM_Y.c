/*******************************************************************************
* File Name: PWM_Y.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the PWM_Y
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Y.h"

uint8 PWM_Y_initVar = 0u;


/*******************************************************************************
* Function Name: PWM_Y_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PWM_Y configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PWM_Y__QUAD == PWM_Y_CONFIG)
        PWM_Y_CONTROL_REG = PWM_Y_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWM_Y_TRIG_CONTROL1_REG  = PWM_Y_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        PWM_Y_SetInterruptMode(PWM_Y_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        PWM_Y_SetCounterMode(PWM_Y_COUNT_DOWN);
        PWM_Y_WritePeriod(PWM_Y_QUAD_PERIOD_INIT_VALUE);
        PWM_Y_WriteCounter(PWM_Y_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (PWM_Y__QUAD == PWM_Y_CONFIG) */

    #if (PWM_Y__TIMER == PWM_Y_CONFIG)
        PWM_Y_CONTROL_REG = PWM_Y_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWM_Y_TRIG_CONTROL1_REG  = PWM_Y_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWM_Y_SetInterruptMode(PWM_Y_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        PWM_Y_WritePeriod(PWM_Y_TC_PERIOD_VALUE );

        #if (PWM_Y__COMPARE == PWM_Y_TC_COMP_CAP_MODE)
            PWM_Y_WriteCompare(PWM_Y_TC_COMPARE_VALUE);

            #if (1u == PWM_Y_TC_COMPARE_SWAP)
                PWM_Y_SetCompareSwap(1u);
                PWM_Y_WriteCompareBuf(PWM_Y_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PWM_Y_TC_COMPARE_SWAP) */
        #endif  /* (PWM_Y__COMPARE == PWM_Y_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (PWM_Y_CY_TCPWM_V2 && PWM_Y_TIMER_UPDOWN_CNT_USED && !PWM_Y_CY_TCPWM_4000)
            PWM_Y_WriteCounter(1u);
        #elif(PWM_Y__COUNT_DOWN == PWM_Y_TC_COUNTER_MODE)
            PWM_Y_WriteCounter(PWM_Y_TC_PERIOD_VALUE);
        #else
            PWM_Y_WriteCounter(0u);
        #endif /* (PWM_Y_CY_TCPWM_V2 && PWM_Y_TIMER_UPDOWN_CNT_USED && !PWM_Y_CY_TCPWM_4000) */
    #endif  /* (PWM_Y__TIMER == PWM_Y_CONFIG) */

    #if (PWM_Y__PWM_SEL == PWM_Y_CONFIG)
        PWM_Y_CONTROL_REG = PWM_Y_CTRL_PWM_BASE_CONFIG;

        #if (PWM_Y__PWM_PR == PWM_Y_PWM_MODE)
            PWM_Y_CONTROL_REG |= PWM_Y_CTRL_PWM_RUN_MODE;
            PWM_Y_WriteCounter(PWM_Y_PWM_PR_INIT_VALUE);
        #else
            PWM_Y_CONTROL_REG |= PWM_Y_CTRL_PWM_ALIGN | PWM_Y_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (PWM_Y_CY_TCPWM_V2 && PWM_Y_PWM_UPDOWN_CNT_USED && !PWM_Y_CY_TCPWM_4000)
                PWM_Y_WriteCounter(1u);
            #elif (PWM_Y__RIGHT == PWM_Y_PWM_ALIGN)
                PWM_Y_WriteCounter(PWM_Y_PWM_PERIOD_VALUE);
            #else 
                PWM_Y_WriteCounter(0u);
            #endif  /* (PWM_Y_CY_TCPWM_V2 && PWM_Y_PWM_UPDOWN_CNT_USED && !PWM_Y_CY_TCPWM_4000) */
        #endif  /* (PWM_Y__PWM_PR == PWM_Y_PWM_MODE) */

        #if (PWM_Y__PWM_DT == PWM_Y_PWM_MODE)
            PWM_Y_CONTROL_REG |= PWM_Y_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (PWM_Y__PWM_DT == PWM_Y_PWM_MODE) */

        #if (PWM_Y__PWM == PWM_Y_PWM_MODE)
            PWM_Y_CONTROL_REG |= PWM_Y_CTRL_PWM_PRESCALER;
        #endif  /* (PWM_Y__PWM == PWM_Y_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        PWM_Y_TRIG_CONTROL1_REG  = PWM_Y_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWM_Y_SetInterruptMode(PWM_Y_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (PWM_Y__PWM_PR == PWM_Y_PWM_MODE)
            PWM_Y_TRIG_CONTROL2_REG =
                    (PWM_Y_CC_MATCH_NO_CHANGE    |
                    PWM_Y_OVERLOW_NO_CHANGE      |
                    PWM_Y_UNDERFLOW_NO_CHANGE);
        #else
            #if (PWM_Y__LEFT == PWM_Y_PWM_ALIGN)
                PWM_Y_TRIG_CONTROL2_REG = PWM_Y_PWM_MODE_LEFT;
            #endif  /* ( PWM_Y_PWM_LEFT == PWM_Y_PWM_ALIGN) */

            #if (PWM_Y__RIGHT == PWM_Y_PWM_ALIGN)
                PWM_Y_TRIG_CONTROL2_REG = PWM_Y_PWM_MODE_RIGHT;
            #endif  /* ( PWM_Y_PWM_RIGHT == PWM_Y_PWM_ALIGN) */

            #if (PWM_Y__CENTER == PWM_Y_PWM_ALIGN)
                PWM_Y_TRIG_CONTROL2_REG = PWM_Y_PWM_MODE_CENTER;
            #endif  /* ( PWM_Y_PWM_CENTER == PWM_Y_PWM_ALIGN) */

            #if (PWM_Y__ASYMMETRIC == PWM_Y_PWM_ALIGN)
                PWM_Y_TRIG_CONTROL2_REG = PWM_Y_PWM_MODE_ASYM;
            #endif  /* (PWM_Y__ASYMMETRIC == PWM_Y_PWM_ALIGN) */
        #endif  /* (PWM_Y__PWM_PR == PWM_Y_PWM_MODE) */

        /* Set other values from customizer */
        PWM_Y_WritePeriod(PWM_Y_PWM_PERIOD_VALUE );
        PWM_Y_WriteCompare(PWM_Y_PWM_COMPARE_VALUE);

        #if (1u == PWM_Y_PWM_COMPARE_SWAP)
            PWM_Y_SetCompareSwap(1u);
            PWM_Y_WriteCompareBuf(PWM_Y_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PWM_Y_PWM_COMPARE_SWAP) */

        #if (1u == PWM_Y_PWM_PERIOD_SWAP)
            PWM_Y_SetPeriodSwap(1u);
            PWM_Y_WritePeriodBuf(PWM_Y_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PWM_Y_PWM_PERIOD_SWAP) */
    #endif  /* (PWM_Y__PWM_SEL == PWM_Y_CONFIG) */
    
}


/*******************************************************************************
* Function Name: PWM_Y_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM_Y.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PWM_Y_BLOCK_CONTROL_REG |= PWM_Y_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (PWM_Y__PWM_SEL == PWM_Y_CONFIG)
        #if (0u == PWM_Y_PWM_START_SIGNAL_PRESENT)
            PWM_Y_TriggerCommand(PWM_Y_MASK, PWM_Y_CMD_START);
        #endif /* (0u == PWM_Y_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PWM_Y__PWM_SEL == PWM_Y_CONFIG) */

    #if (PWM_Y__TIMER == PWM_Y_CONFIG)
        #if (0u == PWM_Y_TC_START_SIGNAL_PRESENT)
            PWM_Y_TriggerCommand(PWM_Y_MASK, PWM_Y_CMD_START);
        #endif /* (0u == PWM_Y_TC_START_SIGNAL_PRESENT) */
    #endif /* (PWM_Y__TIMER == PWM_Y_CONFIG) */
    
    #if (PWM_Y__QUAD == PWM_Y_CONFIG)
        #if (0u != PWM_Y_QUAD_AUTO_START)
            PWM_Y_TriggerCommand(PWM_Y_MASK, PWM_Y_CMD_RELOAD);
        #endif /* (0u != PWM_Y_QUAD_AUTO_START) */
    #endif  /* (PWM_Y__QUAD == PWM_Y_CONFIG) */
}


/*******************************************************************************
* Function Name: PWM_Y_Start
********************************************************************************
*
* Summary:
*  Initializes the PWM_Y with default customizer
*  values when called the first time and enables the PWM_Y.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Y_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PWM_Y_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the PWM_Y_Start() routine.
*
*******************************************************************************/
void PWM_Y_Start(void)
{
    if (0u == PWM_Y_initVar)
    {
        PWM_Y_Init();
        PWM_Y_initVar = 1u;
    }

    PWM_Y_Enable();
}


/*******************************************************************************
* Function Name: PWM_Y_Stop
********************************************************************************
*
* Summary:
*  Disables the PWM_Y.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_BLOCK_CONTROL_REG &= (uint32)~PWM_Y_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PWM_Y. This function is used when
*  configured as a generic PWM_Y and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PWM_Y to operate in
*   Values:
*   - PWM_Y_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PWM_Y_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PWM_Y_MODE_QUAD - Quadrature decoder
*         - PWM_Y_MODE_PWM - PWM
*         - PWM_Y_MODE_PWM_DT - PWM with dead time
*         - PWM_Y_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_MODE_MASK;
    PWM_Y_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PWM_Y_MODE_X1 - Counts on phi 1 rising
*         - PWM_Y_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PWM_Y_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_QUAD_MODE_MASK;
    PWM_Y_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PWM_Y_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PWM_Y_PRESCALE_DIVBY2    - Divide by 2
*         - PWM_Y_PRESCALE_DIVBY4    - Divide by 4
*         - PWM_Y_PRESCALE_DIVBY8    - Divide by 8
*         - PWM_Y_PRESCALE_DIVBY16   - Divide by 16
*         - PWM_Y_PRESCALE_DIVBY32   - Divide by 32
*         - PWM_Y_PRESCALE_DIVBY64   - Divide by 64
*         - PWM_Y_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_PRESCALER_MASK;
    PWM_Y_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM_Y runs
*  continuously or stops when terminal count is reached.  By default the
*  PWM_Y operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_ONESHOT_MASK;
    PWM_Y_CONTROL_REG |= ((uint32)((oneShotEnable & PWM_Y_1BIT_MASK) <<
                                                               PWM_Y_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPWMMode(uint32 modeMask)
{
    PWM_Y_TRIG_CONTROL2_REG = (modeMask & PWM_Y_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PWM_Y_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_PWM_SYNC_KILL_MASK;
    PWM_Y_CONTROL_REG |= ((uint32)((syncKillEnable & PWM_Y_1BIT_MASK)  <<
                                               PWM_Y_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_PWM_STOP_KILL_MASK;
    PWM_Y_CONTROL_REG |= ((uint32)((stopOnKillEnable & PWM_Y_1BIT_MASK)  <<
                                                         PWM_Y_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_PRESCALER_MASK;
    PWM_Y_CONTROL_REG |= ((uint32)((deadTime & PWM_Y_8BIT_MASK) <<
                                                          PWM_Y_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - PWM_Y_INVERT_LINE   - Inverts the line output
*         - PWM_Y_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_INV_OUT_MASK;
    PWM_Y_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PWM_Y_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_WriteCounter(uint32 count)
{
    PWM_Y_COUNTER_REG = (count & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 PWM_Y_ReadCounter(void)
{
    return (PWM_Y_COUNTER_REG & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - PWM_Y_COUNT_UP       - Counts up
*     - PWM_Y_COUNT_DOWN     - Counts down
*     - PWM_Y_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PWM_Y_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_UPDOWN_MASK;
    PWM_Y_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_WritePeriod(uint32 period)
{
    PWM_Y_PERIOD_REG = (period & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWM_Y_ReadPeriod(void)
{
    return (PWM_Y_PERIOD_REG & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_RELOAD_CC_MASK;
    PWM_Y_CONTROL_REG |= (swapEnable & PWM_Y_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_WritePeriodBuf(uint32 periodBuf)
{
    PWM_Y_PERIOD_BUF_REG = (periodBuf & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWM_Y_ReadPeriodBuf(void)
{
    return (PWM_Y_PERIOD_BUF_REG & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_CONTROL_REG &= (uint32)~PWM_Y_RELOAD_PERIOD_MASK;
    PWM_Y_CONTROL_REG |= ((uint32)((swapEnable & PWM_Y_1BIT_MASK) <<
                                                            PWM_Y_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void PWM_Y_WriteCompare(uint32 compare)
{
    #if (PWM_Y_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWM_Y_CY_TCPWM_4000) */

    #if (PWM_Y_CY_TCPWM_4000)
        currentMode = ((PWM_Y_CONTROL_REG & PWM_Y_UPDOWN_MASK) >> PWM_Y_UPDOWN_SHIFT);

        if (((uint32)PWM_Y__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)PWM_Y__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (PWM_Y_CY_TCPWM_4000) */
    
    PWM_Y_COMP_CAP_REG = (compare & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 PWM_Y_ReadCompare(void)
{
    #if (PWM_Y_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWM_Y_CY_TCPWM_4000) */

    #if (PWM_Y_CY_TCPWM_4000)
        currentMode = ((PWM_Y_CONTROL_REG & PWM_Y_UPDOWN_MASK) >> PWM_Y_UPDOWN_SHIFT);
        
        regVal = PWM_Y_COMP_CAP_REG;
        
        if (((uint32)PWM_Y__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWM_Y__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWM_Y_16BIT_MASK);
    #else
        return (PWM_Y_COMP_CAP_REG & PWM_Y_16BIT_MASK);
    #endif /* (PWM_Y_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWM_Y_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void PWM_Y_WriteCompareBuf(uint32 compareBuf)
{
    #if (PWM_Y_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWM_Y_CY_TCPWM_4000) */

    #if (PWM_Y_CY_TCPWM_4000)
        currentMode = ((PWM_Y_CONTROL_REG & PWM_Y_UPDOWN_MASK) >> PWM_Y_UPDOWN_SHIFT);

        if (((uint32)PWM_Y__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)PWM_Y__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (PWM_Y_CY_TCPWM_4000) */
    
    PWM_Y_COMP_CAP_BUF_REG = (compareBuf & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 PWM_Y_ReadCompareBuf(void)
{
    #if (PWM_Y_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWM_Y_CY_TCPWM_4000) */

    #if (PWM_Y_CY_TCPWM_4000)
        currentMode = ((PWM_Y_CONTROL_REG & PWM_Y_UPDOWN_MASK) >> PWM_Y_UPDOWN_SHIFT);

        regVal = PWM_Y_COMP_CAP_BUF_REG;
        
        if (((uint32)PWM_Y__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWM_Y__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWM_Y_16BIT_MASK);
    #else
        return (PWM_Y_COMP_CAP_BUF_REG & PWM_Y_16BIT_MASK);
    #endif /* (PWM_Y_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWM_Y_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 PWM_Y_ReadCapture(void)
{
    return (PWM_Y_COMP_CAP_REG & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 PWM_Y_ReadCaptureBuf(void)
{
    return (PWM_Y_COMP_CAP_BUF_REG & PWM_Y_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_Y_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_Y_TRIG_LEVEL     - Level
*     - PWM_Y_TRIG_RISING    - Rising edge
*     - PWM_Y_TRIG_FALLING   - Falling edge
*     - PWM_Y_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_TRIG_CONTROL1_REG &= (uint32)~PWM_Y_CAPTURE_MASK;
    PWM_Y_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_Y_TRIG_LEVEL     - Level
*     - PWM_Y_TRIG_RISING    - Rising edge
*     - PWM_Y_TRIG_FALLING   - Falling edge
*     - PWM_Y_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_TRIG_CONTROL1_REG &= (uint32)~PWM_Y_RELOAD_MASK;
    PWM_Y_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_Y_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_Y_TRIG_LEVEL     - Level
*     - PWM_Y_TRIG_RISING    - Rising edge
*     - PWM_Y_TRIG_FALLING   - Falling edge
*     - PWM_Y_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_TRIG_CONTROL1_REG &= (uint32)~PWM_Y_START_MASK;
    PWM_Y_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_Y_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_Y_TRIG_LEVEL     - Level
*     - PWM_Y_TRIG_RISING    - Rising edge
*     - PWM_Y_TRIG_FALLING   - Falling edge
*     - PWM_Y_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_TRIG_CONTROL1_REG &= (uint32)~PWM_Y_STOP_MASK;
    PWM_Y_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_Y_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_Y_TRIG_LEVEL     - Level
*     - PWM_Y_TRIG_RISING    - Rising edge
*     - PWM_Y_TRIG_FALLING   - Falling edge
*     - PWM_Y_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_TRIG_CONTROL1_REG &= (uint32)~PWM_Y_COUNT_MASK;
    PWM_Y_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_Y_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - PWM_Y_CMD_CAPTURE    - Trigger Capture/Switch command
*     - PWM_Y_CMD_RELOAD     - Trigger Reload/Index command
*     - PWM_Y_CMD_STOP       - Trigger Stop/Kill command
*     - PWM_Y_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_Y_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_Y_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PWM_Y.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PWM_Y_STATUS_DOWN    - Set if counting down
*     - PWM_Y_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PWM_Y_ReadStatus(void)
{
    return ((PWM_Y_STATUS_REG >> PWM_Y_RUNNING_STATUS_SHIFT) |
            (PWM_Y_STATUS_REG & PWM_Y_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PWM_Y_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PWM_Y_INTR_MASK_TC       - Terminal count mask
*     - PWM_Y_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetInterruptMode(uint32 interruptMask)
{
    PWM_Y_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PWM_Y_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - PWM_Y_INTR_MASK_TC       - Terminal count mask
*     - PWM_Y_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWM_Y_GetInterruptSourceMasked(void)
{
    return (PWM_Y_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PWM_Y_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - PWM_Y_INTR_MASK_TC       - Terminal count mask
*     - PWM_Y_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWM_Y_GetInterruptSource(void)
{
    return (PWM_Y_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PWM_Y_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PWM_Y_INTR_MASK_TC       - Terminal count mask
*     - PWM_Y_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_ClearInterrupt(uint32 interruptMask)
{
    PWM_Y_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PWM_Y_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PWM_Y_INTR_MASK_TC       - Terminal count mask
*     - PWM_Y_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Y_SetInterrupt(uint32 interruptMask)
{
    PWM_Y_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
