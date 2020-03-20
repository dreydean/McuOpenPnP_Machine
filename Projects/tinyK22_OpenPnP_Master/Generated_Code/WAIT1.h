/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : WAIT1.h
**     Project     : tinyK22_OpenPnP_Master
**     Processor   : MK22FN512VLH12
**     Component   : Wait
**     Version     : Component 01.085, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-10-19, 06:30, # CodeGen: 7
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : WAIT1
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Enabled
**            RTOS                                         : FRTOS1
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void WAIT1_Wait10Cycles(void);
**         Wait100Cycles  - void WAIT1_Wait100Cycles(void);
**         WaitCycles     - void WAIT1_WaitCycles(uint16_t cycles);
**         WaitLongCycles - void WAIT1_WaitLongCycles(uint32_t cycles);
**         Waitms         - void WAIT1_Waitms(uint16_t ms);
**         Waitus         - void WAIT1_Waitus(uint16_t us);
**         Waitns         - void WAIT1_Waitns(uint16_t ns);
**         WaitOSms       - void WAIT1_WaitOSms(void);
**         Init           - void WAIT1_Init(void);
**
** * Copyright (c) 2013-2019, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file WAIT1.h
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup WAIT1_module WAIT1 module documentation
**  @{
*/         

#ifndef __WAIT1_H
#define __WAIT1_H

/* MODULE WAIT1. */
#include "MCUC1.h" /* SDK and API used */
#include "WAIT1config.h" /* configuration */

/* other includes needed */
#if WAIT1_CONFIG_USE_RTOS_WAIT
  /* include RTOS header files */
  #include "FRTOS1.h"
  #include "FreeRTOS.h" /* for vTaskDelay() */
  #include "task.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if MCUC1_CONFIG_SDK_VERSION_USED == MCUC1_CONFIG_SDK_PROCESSOR_EXPERT
  #define WAIT1_INSTR_CLOCK_HZ       CPU_CORE_CLK_HZ /* for Kinetis, use core clock as base for instruction execution */
#else
  extern uint32_t SystemCoreClock; /* clock frequency variable defined system_<device>.h of the SDK */
  #define WAIT1_INSTR_CLOCK_HZ       SystemCoreClock  /* core clock frequency in Hz */
#endif
#define WAIT1_NofCyclesMs(ms, hz)  ((ms)*((hz)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define WAIT1_NofCyclesUs(us, hz)  ((us)*(((hz)/1000)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define WAIT1_NofCyclesNs(ns, hz)  (((ns)*(((hz)/1000)/1000))/1000) /* calculates the needed cycles based on bus clock frequency */

#define WAIT1_WAIT_C(cycles) \
     ( (cycles)<=10 ? \
          WAIT1_Wait10Cycles() \
        : WAIT1_WaitCycles((uint16_t)cycles) \
      )                                      /*!< wait for some cycles */


void WAIT1_Wait10Cycles(void);
/*
** ===================================================================
**     Method      :  Wait10Cycles (component Wait)
**
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_Wait100Cycles(void);
/*
** ===================================================================
**     Method      :  Wait100Cycles (component Wait)
**
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_WaitCycles(uint16_t cycles);
/*
** ===================================================================
**     Method      :  WaitCycles (component Wait)
**
**     Description :
**         Wait for a specified number of CPU cycles (16bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_Waitms(uint16_t ms);
/*
** ===================================================================
**     Method      :  Waitms (component Wait)
**
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define WAIT1_Waitus(us)  \
        /*lint -save -e(505,506,522) Constant value Boolean, Redundant left argument to comma. */\
       (  ((WAIT1_NofCyclesUs((us),WAIT1_INSTR_CLOCK_HZ)==0)||(us)==0) ? \
          (void)0 : \
          ( ((us)/1000)==0 ? (void)0 : WAIT1_Waitms((uint16_t)((us)/1000))) \
          , (WAIT1_NofCyclesUs(((us)%1000), WAIT1_INSTR_CLOCK_HZ)==0) ? (void)0 : \
            WAIT1_WAIT_C(WAIT1_NofCyclesUs(((us)%1000), WAIT1_INSTR_CLOCK_HZ)) \
       /*lint -restore */\
       )
/*
** ===================================================================
**     Method      :  Waitus (component Wait)
**
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define WAIT1_Waitns(ns)  \
        /*lint -save -e(505,506,522) Constant value Boolean, Redundant left argument to comma. */\
       (  ((WAIT1_NofCyclesNs((ns), WAIT1_INSTR_CLOCK_HZ)==0)||(ns)==0) ? \
          (void)0 : \
          WAIT1_Waitus((ns)/1000) \
          , (WAIT1_NofCyclesNs((ns)%1000, WAIT1_INSTR_CLOCK_HZ)==0) ? \
              (void)0 : \
              WAIT1_WAIT_C(WAIT1_NofCyclesNs(((ns)%1000), WAIT1_INSTR_CLOCK_HZ)) \
       /*lint -restore */\
       )
/*
** ===================================================================
**     Method      :  Waitns (component Wait)
**
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/

#if WAIT1_CONFIG_USE_RTOS_WAIT
  #define WAIT1_WaitOSms(ms) vTaskDelay(pdMS_TO_TICKS(ms)) /* use FreeRTOS API */
#else
  #define WAIT1_WaitOSms(ms)  WAIT1_Waitms(ms) /* use normal wait */
#endif
/*
** ===================================================================
**     Method      :  WaitOSms (component Wait)
**
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_WaitLongCycles(uint32_t cycles);
/*
** ===================================================================
**     Method      :  WaitLongCycles (component Wait)
**
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

void WAIT1_Init(void);
/*
** ===================================================================
**     Method      :  Init (component Wait)
**
**     Description :
**         Driver initialization routine.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END WAIT1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __WAIT1_H */
/*!
** @}
*/
