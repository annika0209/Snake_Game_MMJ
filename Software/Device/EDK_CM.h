//--------------------------------------------------------
// CMSIS Core Peripheral Access Layer Header File
//--------------------------------------------------------

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/****** Cortex-M Processor Exceptions Numbers *****************************************************/

/* Use this Cortex interrupt numbers if your device is a CORTEX-M device                          */
  NonMaskableInt_IRQn           = -14,      /*!<  2 Cortex-M Non Maskable Interrupt               */
  HardFault_IRQn                = -13,      /*!<  3 Cortex-M Hard Fault Interrupt                 */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M SV Call Interrupt                    */
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M Pend SV Interrupt                    */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M System Tick Interrupt                */

/******  System Specific Interrupt Numbers ********************************************************/
  Timer_IRQn                    = 0,       
  UART_IRQn                     = 1,       

} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Processor and Core Peripherals */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
