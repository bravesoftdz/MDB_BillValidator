/*
*****************************************************************************
**
**      Project     : KAWE_76032
**
**      Component   : Time (LPC1225)
**
**      Modulename  : PUBLIC
**
**      Filename    : Time.c
**
**      Abstract    : This is the device driver  file for the RTX real time chip 
**                    module.
**
**      Compiler    : KEIL C compiler
**
**      Date        : 2014-09-28 16:31:15
**
**      License no. : 9538-154-209-9667     Frank Tsang
**
**      Warning     : This file has been automatically generated.
**                    Do not edit this file if you intend to regenerate it.
**
**      This device driver was created by IAR MakeApp version 
**      4.10C (Atmel megaAVR: 4.00B) for the Atmel megaAVR series of
**      microcontrollers.
**
**      (c)Copyright 2003 IAR Systems.
**      Your rights to this file are explained in the IAR MakeApp 
**      License Agreement. All other rights reserved.
**
*****************************************************************************
*/

/*
**===========================================================================
**  1       GENERAL
**  1.1     Revisions
**
**  Please read the IAR MakeApp for Atmel megaAVR readme file 
**  V1.0
**
**===========================================================================
*/

/*
**===========================================================================
**  1.2     References
** 
**  No   Identification          Name or Description
**===========================================================================
**  
** 
**===========================================================================
*/

/*
**===========================================================================
**  2.      INCLUDE FILES
**  2.1     Standard include files
**===========================================================================
*/

#include <lpc12xx.h>
#include <core_cm0.h>
#include <lpc_types.h>
#include <stdlib.h>
#include <stdio.h>

#include <RTL.h> 
//#include "RT_Agent.h"
#include "Lpc12xx_libcfg_default.h"


/*
**===========================================================================
**  2.2     Application include files
**===========================================================================
*/
#ifndef _IS_INCLUDED_TIME_C_
#define _IS_INCLUDED_TIME_C_

#include "Time.h"
#include "Main.h"

#include "Debug_frmwrk.h"
#include "Uart.h"


#endif

/*
**===========================================================================
**  3.      DECLARATIONS
**  3.1     Internal constants
**===========================================================================
*/


/*
**===========================================================================
**  3.2     Internal macros
**===========================================================================
*/

/*
**===========================================================================
**  3.3     Internal type definitions
**===========================================================================
*/

/*
**===========================================================================
**  3.4     Global variables (declared as 'extern' in some header file)
**===========================================================================
*/


/*
**===========================================================================
**  3.5     Internal function prototypes (defined in Section 5)
**===========================================================================
*/

/*
**===========================================================================
**  3.6     Internal variables
**===========================================================================
*/

/*
**===========================================================================
**  4.      GLOBAL FUNCTIONS (declared as 'extern' in some header file)
**===========================================================================
*/


/*-------------------------------------------------------------------------
function: TIMER16_0_IRQHandler
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
#if 0
void TIMER16_0_IRQHandler(void)
{
	unsigned int int_status_reg;

	int_status_reg = TIM16_GetIntStatusReg (LPC_CT16B0);

	/*clear the interrupt flag of match channel 0 */
	if (int_status_reg & TIM16_INT_MR0) 
	{
		TIM16_ClearIntPendingBit(LPC_CT16B0,TIM16_INT_MR0);
		
		//Timer_Stop_MdbSlave();

		//isr_sem_send(&sem_MdbSlave_Rx);
	}
}
#endif

/*-------------------------------------------------------------------------
function: TIMER32_0_IRQHandler
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
void TIMER32_0_IRQHandler(void)
{
	unsigned int int_status_reg;

	int_status_reg = TIM32_GetIntStatusReg (LPC_CT32B0);

	/*clear the interrupt flag of match channel 0 */
	if (int_status_reg & TIM32_INT_MR0) 
	{
		TIM32_ClearIntPendingBit(LPC_CT32B0,TIM32_INT_MR0);
		
		Timer_Stop_MdbSlave();

		UART_ConfigInts(LPC_UART0, UART_INTCFG_RBR, DISABLE);	
		UART_ConfigInts(LPC_UART0, UART_INTCFG_RLS, DISABLE);	

		isr_sem_send(&sem_MdbSlave_Rx);
		//isr_evt_set(0x0001, tid_MdbSlave);
	}
}

#if 0
void TIMER32_1_IRQHandler(void)
{
	unsigned int int_status_reg;

	int_status_reg = TIM32_GetIntStatusReg (LPC_CT32B1);

	/*clear the interrupt flag of match channel 0 */
	if (int_status_reg & TIM32_INT_MR0) 
	{
		TIM32_ClearIntPendingBit(LPC_CT32B1,TIM32_INT_MR0);
		
		Timer_Stop_ComHost();

		UART_ConfigInts(LPC_UART1, UART_INTCFG_RBR, DISABLE);	
		//UART_ConfigInts(LPC_UART1, UART_INTCFG_THRE, ENABLE); 
		UART_ConfigInts(LPC_UART1, UART_INTCFG_RLS, DISABLE);	

		Uart1RxBuff.Index	= 0;
		isr_evt_set(EVT_TIME_OVER, tid_ComHost);

		//MdbSlave_Timer_IRQHandler();	
		//isr_sem_send(&sem_ComHost_Rx);
	}
}
#endif

/*-------------------------------------------------------------------------
function: Timer_Init_MdbSlave
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
#if 0
void Timer_Init_ComHostPoll(void)
{
	TIM16_InitTypeDef TIM16_InitStruct;
//	TIM32_MATCHTypeDef TIM32_MatchConfigStruct ;

	SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_CT16B0, ENABLE);
	NVIC_DisableIRQ(TIMER_16_0_IRQn);

	/* Initialize timer 0, prescale count time of 10uS */
	TIM16_InitStruct.PrescaleOption = TIM16_PRESCALE_USVAL;
	TIM16_InitStruct.PrescaleValue  = 10;

	/* Set configuration for Tim_config  */
	TIM16_Init(LPC_CT16B0, TIM16_TIMER_MODE, &TIM16_InitStruct);

	/* preemption = 0, sub-priority = 3 */
	NVIC_SetPriority(TIMER_16_0_IRQn, ((0x00 << 3) | 0x03));

	/* Enable interrupt for timer */
	NVIC_EnableIRQ(TIMER_16_0_IRQn);

}
#endif

/*-------------------------------------------------------------------------
function: Timer_Init_MdbSlave
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
void Timer_Init_MdbSlave(void)
{
	TIM32_InitTypeDef TIM32_InitStruct;
//	TIM32_MATCHTypeDef TIM32_MatchConfigStruct ;

	SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_CT32B0, ENABLE);
	NVIC_DisableIRQ(TIMER_32_0_IRQn);

	/* Initialize timer 0, prescale count time of 10uS */
	TIM32_InitStruct.PrescaleOption = TIM32_PRESCALE_USVAL;
	TIM32_InitStruct.PrescaleValue  = 10;

	/* Set configuration for Tim_config  */
	TIM32_Init(LPC_CT32B0, TIM32_MODE_TIMER, &TIM32_InitStruct);

	/* preemption = 0, sub-priority = 3 */
	NVIC_SetPriority(TIMER_32_0_IRQn, ((0x00 << 3) | 0x03));

	/* Enable interrupt for timer */
	NVIC_EnableIRQ(TIMER_32_0_IRQn);

}


#if 0
void Timer_Init_ComHost(void)
{
	TIM32_InitTypeDef TIM32_InitStruct;
//	TIM32_MATCHTypeDef TIM32_MatchConfigStruct ;

	SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_CT32B1, ENABLE);
	NVIC_DisableIRQ(TIMER_32_1_IRQn);

	/* Initialize timer 0, prescale count time of 1000uS */
	TIM32_InitStruct.PrescaleOption = TIM32_PRESCALE_USVAL;
	TIM32_InitStruct.PrescaleValue  = 1000;

	/* Set configuration for Tim_config  */
	TIM32_Init(LPC_CT32B1, TIM32_MODE_TIMER, &TIM32_InitStruct);

	/* preemption = 0, sub-priority = 3 */
	NVIC_SetPriority(TIMER_32_1_IRQn, ((0x00 << 3) | 0x03));

	/* Enable interrupt for timer */
	NVIC_EnableIRQ(TIMER_32_1_IRQn);

}
#endif

/*-------------------------------------------------------------------------
function: Timer_Start_ComHostPoll
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
#if 0
void Timer_Start_ComHostPoll( U16 u16_10usUnits )
{
	TIM16_MATCHTypeDef TIM16_MatchConfigStruct ;

	/* To stop timer16B0 */
	TIM16_Cmd(LPC_CT16B0, DISABLE);

	/* Match channel 0, MR0 */
	TIM16_MatchConfigStruct.MatchChannel = TIM16_MATCH_CHANNEL0;
	/* Enable interrupt when MR0 matches the value in TC register */
	TIM16_MatchConfigStruct.IntOnMatch	 = TRUE;
	/* Enable reset on MR0: TIMER will reset if MR0 matches it */
	TIM16_MatchConfigStruct.ResetOnMatch = TRUE;
	/* No Stop on MR0 if MR0 matches it */
	TIM16_MatchConfigStruct.StopOnMatch = FALSE;
	/* Toggle MR0 pin if MR0 matches it */
	TIM16_MatchConfigStruct.ExtMatchOutputType =TIM16_EXTMATCH_NOTHING;
	/* Set Match value, count value of 10uS */
	TIM16_MatchConfigStruct.MatchValue = u16_10usUnits;
	
	TIM16_ConfigMatch(LPC_CT16B0, &TIM16_MatchConfigStruct);

	TIM16_ResetCounter(LPC_CT16B0);

	TIM16_ClearIntPendingBit(LPC_CT16B0, TIM16_INT_MR0);

	/* To start timer16B0 */
	TIM16_Cmd(LPC_CT16B0, ENABLE);
}
#endif 
/*-------------------------------------------------------------------------
function: Timer_Start_MdbSlave
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
void Timer_Start_MdbSlave( U16 u16_10usUnits )
{
	TIM32_MATCHTypeDef TIM32_MatchConfigStruct ;

	/* To stop timer32B0 */
	TIM32_Cmd(LPC_CT32B0, DISABLE);

	/* Match channel 0, MR0 */
	TIM32_MatchConfigStruct.MatchChannel = TIM32_MATCH_CHANNEL0;
	/* Enable interrupt when MR0 matches the value in TC register */
	TIM32_MatchConfigStruct.IntOnMatch	 = TRUE;
	/* Enable reset on MR0: TIMER will reset if MR0 matches it */
	TIM32_MatchConfigStruct.ResetOnMatch = TRUE;
	/* No Stop on MR0 if MR0 matches it */
	TIM32_MatchConfigStruct.StopOnMatch = FALSE;
	/* Toggle MR0 pin if MR0 matches it */
	TIM32_MatchConfigStruct.ExtMatchOutputType =TIM32_EXTMATCH_NOTHING;
	/* Set Match value, count value of 10uS */
	TIM32_MatchConfigStruct.MatchValue = u16_10usUnits;
	
	TIM32_ConfigMatch(LPC_CT32B0, &TIM32_MatchConfigStruct);

	TIM32_ResetCounter(LPC_CT32B0);

	TIM32_ClearIntPendingBit(LPC_CT32B0, TIM32_INT_MR0);

	/* To start timer32B0 */
	TIM32_Cmd(LPC_CT32B0, ENABLE);
}

#if 0 
void Timer_Start_ComHost( U16 u16_1msUnits )
{
	TIM32_MATCHTypeDef TIM32_MatchConfigStruct ;

	/* To stop timer32B1 */
	TIM32_Cmd(LPC_CT32B1, DISABLE);

	/* Match channel 0, MR0 */
	TIM32_MatchConfigStruct.MatchChannel = TIM32_MATCH_CHANNEL0;
	/* Enable interrupt when MR0 matches the value in TC register */
	TIM32_MatchConfigStruct.IntOnMatch   = TRUE;
	/* Enable reset on MR0: TIMER will reset if MR0 matches it */
	TIM32_MatchConfigStruct.ResetOnMatch = TRUE;
	/* No Stop on MR0 if MR0 matches it */
	TIM32_MatchConfigStruct.StopOnMatch = FALSE;
	/* Toggle MR0 pin if MR0 matches it */
	TIM32_MatchConfigStruct.ExtMatchOutputType =TIM32_EXTMATCH_NOTHING;
	/* Set Match value, count value of 1000uS */
	TIM32_MatchConfigStruct.MatchValue = u16_1msUnits;

	TIM32_ConfigMatch(LPC_CT32B1, &TIM32_MatchConfigStruct);

	TIM32_ResetCounter(LPC_CT32B1);

	TIM32_ClearIntPendingBit(LPC_CT32B1, TIM32_INT_MR0);

	/* To start timer32B1 */
	TIM32_Cmd(LPC_CT32B1, ENABLE);
}
#endif

/*-------------------------------------------------------------------------
function: Timer_Stop_MdbSlave
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
void Timer_Stop_MdbSlave( void )
{

	/* To stop timer32B0 */
	TIM32_Cmd(LPC_CT32B0, DISABLE);

	TIM32_ResetCounter(LPC_CT32B0);

	TIM32_ClearIntPendingBit(LPC_CT32B0, TIM32_INT_MR0);
}

#if 0
void Timer_Stop_ComHost( void )
{

	/* To stop timer32B1 */
	TIM32_Cmd(LPC_CT32B1, DISABLE);

	TIM32_ResetCounter(LPC_CT32B1);

	TIM32_ClearIntPendingBit(LPC_CT32B1, TIM32_INT_MR0);
}
#endif

/*-------------------------------------------------------------------------
function: MdbSlave_Rx
function: As a MDB slave, the mode bit High means the ADDRESS byte
-------------------------------------------------------------------------*/
#if 0
void MdbSlave_Timer_IRQHandler(void)
{
	U8 u8_MdbCmd;
	

//	if (u8_MdbSlave_RxFcc != p8_MdbSlave_RxBuff[u8_MdbSlave_RxIndex - 1])
//	{
//		u8_Uart0_State = UART_IDLE;
//	}
//	else
//	{	
	if (Uart0RxBuff.Fcc != Uart0RxBuff.Data[Uart0RxBuff.Index - 1])
	{
		u8_Uart0_State = UART_IDLE;
	}
	else
	{	
		u8_Uart0_State = UART_WAIT;

		u8_MdbCmd = Uart0RxBuff.Data[0];

		switch(u8_MdbCmd)
		{
		case MDBCMD_CASHLESS_RESET:
			MdbSlave_Response(ACK);
			break;
		case MDBCMD_CASHLESS_SETUP:
			MdbSlave_Responses(&pCashlessSetup, sizeof(pCashlessSetup));
			break;
		case MDBCMD_CASHLESS_POLL:
			MdbSlave_Response(ACK);
			break;
		case MDBCMD_CASHLESS_VEND:
			break;
		case MDBCMD_CASHLESS_READER:
			break;
		case MDBCMD_CASHLESS_REVALUE:
			break;
		case MDBCMD_CASHLESS_EXPASION:
			break;
		default:
			break;
		}
	}
	
}
#endif




/*
**===========================================================================
** END OF FILE
**===========================================================================
*/ 

