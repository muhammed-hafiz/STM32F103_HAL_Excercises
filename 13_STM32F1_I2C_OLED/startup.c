#include <stdint.h>
#include "stm32f10x.h"

/* Forward declarations */
void Reset_Handler(void);
void Default_Handler(void);
//void EXTI15_10_Handler(void);
void SysTick_Handler(void);

//void USART2_IRQHandler();
//void USART3_IRQHandler();

/* Linker script symbols */
extern uint32_t _estack;
extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

#define SCB_VTOR ((volatile uint32_t*)0xE000ED08)

/* Weak aliases for interrupt handlers */
__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler(void);

/* Interrupt Vector Table */
__attribute__((section(".isr_vector")))
void (*const g_pfnVectors[])(void) = {
    (void*)&_estack,        /* Stack pointer */
    Reset_Handler,
    NMI_Handler,            /* NMI Handler */
    HardFault_Handler,      /* Hard Fault Handler */
    MemManage_Handler,      /* MPU Fault Handler */
    BusFault_Handler,       /* Bus Fault Handler */
    UsageFault_Handler,     /* Usage Fault Handler */
    0,                      /* Reserved */
    0,                      /* Reserved */
    0,                      /* Reserved */
    0,                      /* Reserved */
    SVC_Handler,            /* SVCall Handler */
    DebugMon_Handler,       /* Debug Monitor Handler */
    0,                      /* Reserved */
    PendSV_Handler,         /* PendSV Handler */
    SysTick_Handler,        /* SysTick Handler */
    
    /* External Interrupts */
    [16] = 0, [17] = 0, [18] = 0, [19] = 0, [20] = 0,
    [21] = 0, [22] = 0, [23] = 0, [24] = 0, [25] = 0,
    [26] = 0, [27] = 0, [28] = 0, [29] = 0, [30] = 0,
    [31] = 0, [32] = 0, [33] = 0, [34] = 0, [35] = 0,
    [36] = 0, [37] = 0, [38] = 0, [39] = 0, [40] = 0,
    [41] = 0, [42] = 0, [43] = 0, [44] = 0, [45] = 0,
    [46] = 0, [47] = 0, [48] = 0, [49] = 0, [50] = 0,
    [51] = 0, [52] = 0, [53] = 0, [54] = 0, [55] = 0,
    [56] = 0  /* EXTI15_10 at position 56 (16 + 40) */
};

/* Default Handler */
void Default_Handler(void) { while(1); }

/* Reset Handler */
void Reset_Handler(void) {
    /* Copy data section */
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while(dst < &_edata) *dst++ = *src++;

    /* Clear bss section */
    dst = &_sbss;
    while(dst < &_ebss) *dst++ = 0;

    *SCB_VTOR = 0x08000000;  // Point VTOR to flash where your vector table is


    // initialize system clock
    clock_init();

    /* Call main */
    extern int main(void);
    main();
}