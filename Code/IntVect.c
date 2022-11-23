/******************************************************************************************
  Filename    : IntVect.c
  
  Core        : ARM Cortex®-M7
  
  MCU         : STM32H7A3ZI
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.11.2022
  
  Description : Interrupt Vector Table for STM32H7A3ZI
  
******************************************************************************************/
//=============================================================================
// Linker symbols
//=============================================================================
extern void __SYS_STACK_TOP(void);

//=============================================================================
// Extern function prototype
//=============================================================================
extern void Startup_Init(void);

//=============================================================================
// Functions prototype
//=============================================================================
static void UndefinedHandler(void);

void Isr_NonMaskableInt_IRQn         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HardFault_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_MemoryManagement_IRQn       (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BusFault_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UsageFault_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SVCall_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DebugMonitor_IRQn           (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_PendSV_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SysTick_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_WWDG1_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_PVD_PVM_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RTC_TAMP_STAMP_CSS_LSE_IRQn (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RTC_WKUP_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FLASH_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RCC_IRQn                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI0_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI1_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI2_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI3_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI4_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR0_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR1_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR2_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR3_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR4_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR5_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA_STR6_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ADC1_2_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FDCAN1_IT0_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FDCAN2_IT0_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FDCAN1_IT1_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FDCAN2_IT1_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI9_5_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_BRK_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_UP_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM1_TRG_COM_IRQn           (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM_CC_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM2_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM3_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM4_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C1_EV_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C1_ER_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C2_EV_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C2_ER_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI1_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI2_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART1_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART2_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART3_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_EXTI15_10_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_RTC_ALARM_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_BRK_TIM12_IRQn         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_UP_TIM13_IRQn          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_TRG_COM_TIM14_IRQn     (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM8_CC_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA1_STR7_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FMC_IRQn                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SDMMC1_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM5_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI3_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART4_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART5_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM6_DAC_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM7_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR0_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR1_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR2_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR3_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR4_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ETH_IRQn                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ETH_WKUP_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FDCAN_CAL_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR5_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR6_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2_STR7_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_USART6_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C3_EV_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C3_ER_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_HS_EP1_OUT_IRQn         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_HS_EP1_IN_IRQn          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_HS_WKUP_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_HS_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DCMI_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CRYP_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HASH_RNG_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_FPU_IRQn                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART7_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART8_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI4_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI5_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPI6_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SAI1_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LTDC_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LTDC_ER_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMA2D_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SAI2_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_QUADSPI_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LPTIM1_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CEC_IRQn                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C4_EV_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C4_ER_IRQn                (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SPDIF_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_FS_EP1_OUT_IRQn         (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_FS_EP1_IN_IRQn          (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_FS_WKUP_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_OTG_FS_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMAMUX1_OV_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM1_MST_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM1_TIMA_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM_TIMB_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM1_TIMC_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM1_TIMD_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM_TIME_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HRTIM1_FLT_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DFSDM1_FLT0_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DFSDM1_FLT1_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DFSDM1_FLT2_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DFSDM1_FLT3_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SAI3_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SWPMI1_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM15_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM16_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_TIM17_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_MDIOS_WKUP_IRQn             (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_MDIOS_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_JPEG_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_MDMA_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SDMMC_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_HSEM0_IRQn                  (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_ADC3_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_DMAMUX2_OVR_IRQn            (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH1_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH2_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH3_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH4_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH5_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH6_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH7_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_BDMA_CH8_IRQn               (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_COMP_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LPTIM2_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LPTIM3_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LPTIM4_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LPTIM5_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_LPUART_IRQn                 (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_WWDG1_RST_IRQn              (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_CRS_IRQn                    (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_SAI4_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));
void Isr_WKUP_IRQn                   (void) __attribute__((weak, alias("UndefinedHandler")));

//=============================================================================
// Types definition
//=============================================================================
typedef void (*InterruptHandler)(void);

//=============================================================================
// Local function
//=============================================================================
static void UndefinedHandler(void)
{
  for(;;);
}

//=============================================================================
// Interrupt vector table
//=============================================================================
const InterruptHandler __attribute__((section (".intvect"), aligned(512))) InterruptVectorTable[] =
{
    (InterruptHandler)__SYS_STACK_TOP,                 /* Stack pointer                                                                   */
    (InterruptHandler)&Startup_Init,                   /* Reset Vector, invoked on Power up and warm reset                                */
    (InterruptHandler)&Isr_NonMaskableInt_IRQn,        /* Non maskable Interrupt, cannot be stopped or preempted                          */
    (InterruptHandler)&Isr_HardFault_IRQn,             /* Hard Fault, all classes of Fault                                                */
    (InterruptHandler)&Isr_MemoryManagement_IRQn,      /* Memory Management, MPU mismatch, including Access Violation and No Match        */
    (InterruptHandler)&Isr_BusFault_IRQn,              /* Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault  */
    (InterruptHandler)&Isr_UsageFault_IRQn,            /* Usage Fault, i.e. Undef Instruction, Illegal State Transition                   */
    (InterruptHandler)&UndefinedHandler,               /* Reserved                                                                        */
    (InterruptHandler)&UndefinedHandler,               /* Reserved                                                                        */
    (InterruptHandler)&UndefinedHandler,               /* Reserved                                                                        */
    (InterruptHandler)&UndefinedHandler,               /* Reserved                                                                        */
    (InterruptHandler)&Isr_SVCall_IRQn,                /* System Service Call via SVC instruction                                         */
    (InterruptHandler)&UndefinedHandler,               /* Reserved                                                                        */
    (InterruptHandler)&UndefinedHandler,               /* Reserved                                                                        */
    (InterruptHandler)&Isr_PendSV_IRQn,                /* Pendable request for system service                                             */
    (InterruptHandler)&Isr_SysTick_IRQn,               /* System Tick Timer                                                               */
    (InterruptHandler)&Isr_WWDG1_IRQn,                 /* Window Watchdog interrupt                                                       */
    (InterruptHandler)&Isr_PVD_PVM_IRQn,               /* PVD through EXTI line                                                           */
    (InterruptHandler)&Isr_RTC_TAMP_STAMP_CSS_LSE_IRQn,/* RTC tamper, timestamp                                                           */
    (InterruptHandler)&Isr_RTC_WKUP_IRQn,              /* RTC Wakeup interrupt                                                            */
    (InterruptHandler)&Isr_FLASH_IRQn,                 /* Flash memory                                                                    */
    (InterruptHandler)&Isr_RCC_IRQn,                   /* RCC global interrupt                                                            */
    (InterruptHandler)&Isr_EXTI0_IRQn,                 /* EXTI Line 0 interrupt                                                           */
    (InterruptHandler)&Isr_EXTI1_IRQn,                 /* EXTI Line 1 interrupt                                                           */
    (InterruptHandler)&Isr_EXTI2_IRQn,                 /* EXTI Line 2 interrupt                                                           */
    (InterruptHandler)&Isr_EXTI3_IRQn,                 /* EXTI Line 3interrupt                                                            */
    (InterruptHandler)&Isr_EXTI4_IRQn,                 /* EXTI Line 4interrupt                                                            */
    (InterruptHandler)&Isr_DMA_STR0_IRQn,              /* DMA1 Stream0                                                                    */
    (InterruptHandler)&Isr_DMA_STR1_IRQn,              /* DMA1 Stream1                                                                    */
    (InterruptHandler)&Isr_DMA_STR2_IRQn,              /* DMA1 Stream2                                                                    */
    (InterruptHandler)&Isr_DMA_STR3_IRQn,              /* DMA1 Stream3                                                                    */
    (InterruptHandler)&Isr_DMA_STR4_IRQn,              /* DMA1 Stream4                                                                    */
    (InterruptHandler)&Isr_DMA_STR5_IRQn,              /* DMA1 Stream5                                                                    */
    (InterruptHandler)&Isr_DMA_STR6_IRQn,              /* DMA1 Stream6                                                                    */
    (InterruptHandler)&Isr_ADC1_2_IRQn,                /* ADC1 and ADC2                                                                   */
    (InterruptHandler)&Isr_FDCAN1_IT0_IRQn,            /* FDCAN1 Interrupt 0                                                              */
    (InterruptHandler)&Isr_FDCAN2_IT0_IRQn,            /* FDCAN2 Interrupt 0                                                              */
    (InterruptHandler)&Isr_FDCAN1_IT1_IRQn,            /* FDCAN1 Interrupt 1                                                              */
    (InterruptHandler)&Isr_FDCAN2_IT1_IRQn,            /* FDCAN2 Interrupt 1                                                              */
    (InterruptHandler)&Isr_EXTI9_5_IRQn,               /* EXTI Line[9:5] interrupts                                                       */
    (InterruptHandler)&Isr_TIM1_BRK_IRQn,              /* TIM1 break interrupt                                                            */
    (InterruptHandler)&Isr_TIM1_UP_IRQn,               /* TIM1 update interrupt                                                           */
    (InterruptHandler)&Isr_TIM1_TRG_COM_IRQn,          /* TIM1 trigger and commutation                                                    */
    (InterruptHandler)&Isr_TIM_CC_IRQn,                /* TIM1 capture / compare                                                          */
    (InterruptHandler)&Isr_TIM2_IRQn,                  /* TIM2 global interrupt                                                           */
    (InterruptHandler)&Isr_TIM3_IRQn,                  /* TIM3 global interrupt                                                           */
    (InterruptHandler)&Isr_TIM4_IRQn,                  /* TIM4 global interrupt                                                           */
    (InterruptHandler)&Isr_I2C1_EV_IRQn,               /* I2C1 event interrupt                                                            */
    (InterruptHandler)&Isr_I2C1_ER_IRQn,               /* I2C1 error interrupt                                                            */
    (InterruptHandler)&Isr_I2C2_EV_IRQn,               /* I2C2 event interrupt                                                            */
    (InterruptHandler)&Isr_I2C2_ER_IRQn,               /* I2C2 error interrupt                                                            */
    (InterruptHandler)&Isr_SPI1_IRQn,                  /* SPI1 global interrupt                                                           */
    (InterruptHandler)&Isr_SPI2_IRQn,                  /* SPI2 global interrupt                                                           */
    (InterruptHandler)&Isr_USART1_IRQn,                /* USART1 global interrupt                                                         */
    (InterruptHandler)&Isr_USART2_IRQn,                /* USART2 global interrupt                                                         */
    (InterruptHandler)&Isr_USART3_IRQn,                /* USART3 global interrupt                                                         */
    (InterruptHandler)&Isr_EXTI15_10_IRQn,             /* EXTI Line[15:10] interrupts                                                     */
    (InterruptHandler)&Isr_RTC_ALARM_IRQn,             /* RTC alarms (A and B)                                                            */
    (InterruptHandler)&Isr_TIM8_BRK_TIM12_IRQn,        /* TIM8 and 12 break global                                                        */
    (InterruptHandler)&Isr_TIM8_UP_TIM13_IRQn,         /* TIM8 and 13 update global                                                       */
    (InterruptHandler)&Isr_TIM8_TRG_COM_TIM14_IRQn,    /* TIM8 and 14 trigger /commutation and global                                     */
    (InterruptHandler)&Isr_TIM8_CC_IRQn,               /* TIM8 capture / compare                                                          */
    (InterruptHandler)&Isr_DMA1_STR7_IRQn,             /* DMA1 Stream7                                                                    */
    (InterruptHandler)&Isr_FMC_IRQn,                   /* FMC global interrupt                                                            */
    (InterruptHandler)&Isr_SDMMC1_IRQn,                /* SDMMC global interrupt                                                          */
    (InterruptHandler)&Isr_TIM5_IRQn,                  /* TIM5 global interrupt                                                           */
    (InterruptHandler)&Isr_SPI3_IRQn,                  /* SPI3 global interrupt                                                           */
    (InterruptHandler)&Isr_UART4_IRQn,                 /* UART4 global interrupt                                                          */
    (InterruptHandler)&Isr_UART5_IRQn,                 /* UART5 global interrupt                                                          */
    (InterruptHandler)&Isr_TIM6_DAC_IRQn,              /* TIM6 global interrupt                                                           */
    (InterruptHandler)&Isr_TIM7_IRQn,                  /* TIM7 global interrupt                                                           */
    (InterruptHandler)&Isr_DMA2_STR0_IRQn,             /* DMA2 Stream0 interrupt                                                          */
    (InterruptHandler)&Isr_DMA2_STR1_IRQn,             /* DMA2 Stream1 interrupt                                                          */
    (InterruptHandler)&Isr_DMA2_STR2_IRQn,             /* DMA2 Stream2 interrupt                                                          */
    (InterruptHandler)&Isr_DMA2_STR3_IRQn,             /* DMA2 Stream3 interrupt                                                          */
    (InterruptHandler)&Isr_DMA2_STR4_IRQn,             /* DMA2 Stream4 interrupt                                                          */
    (InterruptHandler)&Isr_ETH_IRQn,                   /* Ethernet global interrupt                                                       */
    (InterruptHandler)&Isr_ETH_WKUP_IRQn,              /* Ethernet wakeup through EXTI                                                    */
    (InterruptHandler)&Isr_FDCAN_CAL_IRQn,             /* CAN2TX interrupts                                                               */
    (InterruptHandler)&Isr_DMA2_STR5_IRQn,             /* DMA2 Stream5 interrupt                                                          */
    (InterruptHandler)&Isr_DMA2_STR6_IRQn,             /* DMA2 Stream6 interrupt                                                          */
    (InterruptHandler)&Isr_DMA2_STR7_IRQn,             /* DMA2 Stream7 interrupt                                                          */
    (InterruptHandler)&Isr_USART6_IRQn,                /* USART6 global interrupt                                                         */
    (InterruptHandler)&Isr_I2C3_EV_IRQn,               /* I2C3 event interrupt                                                            */
    (InterruptHandler)&Isr_I2C3_ER_IRQn,               /* I2C3 error interrupt                                                            */
    (InterruptHandler)&Isr_OTG_HS_EP1_OUT_IRQn,        /* OTG_HS out global interrupt                                                     */
    (InterruptHandler)&Isr_OTG_HS_EP1_IN_IRQn,         /* OTG_HS in global interrupt                                                      */
    (InterruptHandler)&Isr_OTG_HS_WKUP_IRQn,           /* OTG_HS wakeup interrupt                                                         */
    (InterruptHandler)&Isr_OTG_HS_IRQn,                /* OTG_HS global interrupt                                                         */
    (InterruptHandler)&Isr_DCMI_IRQn,                  /* DCMI global interrupt                                                           */
    (InterruptHandler)&Isr_CRYP_IRQn,                  /* CRYP global interrupt                                                           */
    (InterruptHandler)&Isr_HASH_RNG_IRQn,              /* HASH and RNG                                                                    */
    (InterruptHandler)&Isr_FPU_IRQn,                   /* CPU FPU                                                                         */
    (InterruptHandler)&Isr_UART7_IRQn,                 /* UART7 global interrupt                                                          */
    (InterruptHandler)&Isr_UART8_IRQn,                 /* UART8 global interrupt                                                          */
    (InterruptHandler)&Isr_SPI4_IRQn,                  /* SPI4 global interrupt                                                           */
    (InterruptHandler)&Isr_SPI5_IRQn,                  /* SPI5 global interrupt                                                           */
    (InterruptHandler)&Isr_SPI6_IRQn,                  /* SPI6 global interrupt                                                           */
    (InterruptHandler)&Isr_SAI1_IRQn,                  /* SAI1 global interrupt                                                           */
    (InterruptHandler)&Isr_LTDC_IRQn,                  /* LCD-TFT global interrupt                                                        */
    (InterruptHandler)&Isr_LTDC_ER_IRQn,               /* LCD-TFT error interrupt                                                         */
    (InterruptHandler)&Isr_DMA2D_IRQn,                 /* DMA2D global interrupt                                                          */
    (InterruptHandler)&Isr_SAI2_IRQn,                  /* SAI2 global interrupt                                                           */
    (InterruptHandler)&Isr_QUADSPI_IRQn,               /* QuadSPI global interrupt                                                        */
    (InterruptHandler)&Isr_LPTIM1_IRQn,                /* LPTIM1 global interrupt                                                         */
    (InterruptHandler)&Isr_CEC_IRQn,                   /* HDMI-CEC global interrupt                                                       */
    (InterruptHandler)&Isr_I2C4_EV_IRQn,               /* I2C4 event interrupt                                                            */
    (InterruptHandler)&Isr_I2C4_ER_IRQn,               /* I2C4 error interrupt                                                            */
    (InterruptHandler)&Isr_SPDIF_IRQn,                 /* SPDIFRX global interrupt                                                        */
    (InterruptHandler)&Isr_OTG_FS_EP1_OUT_IRQn,        /* OTG_FS out global interrupt                                                     */
    (InterruptHandler)&Isr_OTG_FS_EP1_IN_IRQn,         /* OTG_FS in global interrupt                                                      */
    (InterruptHandler)&Isr_OTG_FS_WKUP_IRQn,           /* OTG_FS wakeup                                                                   */
    (InterruptHandler)&Isr_OTG_FS_IRQn,                /* OTG_FS global interrupt                                                         */
    (InterruptHandler)&Isr_DMAMUX1_OV_IRQn,            /* DMAMUX1 overrun interrupt                                                       */
    (InterruptHandler)&Isr_HRTIM1_MST_IRQn,            /* HRTIM1 master timer interrupt                                                   */
    (InterruptHandler)&Isr_HRTIM1_TIMA_IRQn,           /* HRTIM1 timer A interrupt                                                        */
    (InterruptHandler)&Isr_HRTIM_TIMB_IRQn,            /* HRTIM1 timer B interrupt                                                        */
    (InterruptHandler)&Isr_HRTIM1_TIMC_IRQn,           /* HRTIM1 timer C interrupt                                                        */
    (InterruptHandler)&Isr_HRTIM1_TIMD_IRQn,           /* HRTIM1 timer D interrupt                                                        */
    (InterruptHandler)&Isr_HRTIM_TIME_IRQn,            /* HRTIM1 timer E interrupt                                                        */
    (InterruptHandler)&Isr_HRTIM1_FLT_IRQn,            /* HRTIM1 fault interrupt                                                          */
    (InterruptHandler)&Isr_DFSDM1_FLT0_IRQn,           /* DFSDM1 filter 0 interrupt                                                       */
    (InterruptHandler)&Isr_DFSDM1_FLT1_IRQn,           /* DFSDM1 filter 1 interrupt                                                       */
    (InterruptHandler)&Isr_DFSDM1_FLT2_IRQn,           /* DFSDM1 filter 2 interrupt                                                       */
    (InterruptHandler)&Isr_DFSDM1_FLT3_IRQn,           /* DFSDM1 filter 3 interrupt                                                       */
    (InterruptHandler)&Isr_SAI3_IRQn,                  /* SAI3 global interrupt                                                           */
    (InterruptHandler)&Isr_SWPMI1_IRQn,                /* SWPMI global interrupt                                                          */
    (InterruptHandler)&Isr_TIM15_IRQn,                 /* TIM15 global interrupt                                                          */
    (InterruptHandler)&Isr_TIM16_IRQn,                 /* TIM16 global interrupt                                                          */
    (InterruptHandler)&Isr_TIM17_IRQn,                 /* TIM17 global interrupt                                                          */
    (InterruptHandler)&Isr_MDIOS_WKUP_IRQn,            /* MDIOS wakeup                                                                    */
    (InterruptHandler)&Isr_MDIOS_IRQn,                 /* MDIOS global interrupt                                                          */
    (InterruptHandler)&Isr_JPEG_IRQn,                  /* JPEG global interrupt                                                           */
    (InterruptHandler)&Isr_MDMA_IRQn,                  /* MDMA                                                                            */
    (InterruptHandler)&Isr_SDMMC_IRQn,                 /* SDMMC global interrupt                                                          */
    (InterruptHandler)&Isr_HSEM0_IRQn,                 /* HSEM global interrupt 1                                                         */
    (InterruptHandler)&Isr_ADC3_IRQn,                  /* ADC3 global interrupt                                                           */
    (InterruptHandler)&Isr_DMAMUX2_OVR_IRQn,           /* DMAMUX2 overrun interrupt                                                       */
    (InterruptHandler)&Isr_BDMA_CH1_IRQn,              /* BDMA channel 1 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH2_IRQn,              /* BDMA channel 2 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH3_IRQn,              /* BDMA channel 3 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH4_IRQn,              /* BDMA channel 4 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH5_IRQn,              /* BDMA channel 5 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH6_IRQn,              /* BDMA channel 6 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH7_IRQn,              /* BDMA channel 7 interrupt                                                        */
    (InterruptHandler)&Isr_BDMA_CH8_IRQn,              /* BDMA channel 8 interrupt                                                        */
    (InterruptHandler)&Isr_COMP_IRQn,                  /* COMP1 and COMP2                                                                 */
    (InterruptHandler)&Isr_LPTIM2_IRQn,                /* LPTIM2 timer interrupt                                                          */
    (InterruptHandler)&Isr_LPTIM3_IRQn,                /* LPTIM2 timer interrupt                                                          */
    (InterruptHandler)&Isr_LPTIM4_IRQn,                /* LPTIM2 timer interrupt                                                          */
    (InterruptHandler)&Isr_LPTIM5_IRQn,                /* LPTIM2 timer interrupt                                                          */
    (InterruptHandler)&Isr_LPUART_IRQn,                /* LPUART global interrupt                                                         */
    (InterruptHandler)&Isr_WWDG1_RST_IRQn,             /* Window Watchdog interrupt                                                       */
    (InterruptHandler)&Isr_CRS_IRQn,                   /* Clock Recovery System globa                                                     */
    (InterruptHandler)&Isr_SAI4_IRQn,                  /* SAI4 global interrupt                                                           */
    (InterruptHandler)&Isr_WKUP_IRQn                   /* WKUP1 to WKUP6 pins                                                             */
};
