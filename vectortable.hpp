// Filename: interrupthandling.hpp
// Created by by Sergey Kolody  on 08.08.2020 aka Lamerok

#pragma once
#include "intrinsics.h"
#include <cstdint>
#include <cpp/array>
#include "machinetimerregisters.hpp" //for MACHINETIMER
#include "softwaretimerconfig.hpp" // for AppTimerService
#include "eclicregisters.hpp"

struct DummyModule
{
    static void HandleInterrupt()
    {
        for(;;)
        {
            asm volatile("") ;
        }
    }
} ;


struct SystemTimer
{
    static void HandleInterrupt()
    {
        AppTimerService::OnSystemTick() ;
        MACHINETIMER::MTIME::Write(0U);
    }
};

using tInterruptFunction = void(*)() ;

inline constexpr std::array<tInterruptFunction,87> InterruptVectorTable
{
        nullptr,
        nullptr,
        nullptr,
        DummyModule::HandleInterrupt,//eclic_msip_handler,
        nullptr,
        nullptr,
        nullptr,
        SystemTimer::HandleInterrupt, //eclic_mtip_handler,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        DummyModule::HandleInterrupt,//eclic_bwei_handler,
        DummyModule::HandleInterrupt, //eclic_pmovi_handler,
        DummyModule::HandleInterrupt, //WWDGT_IRQHandler,
        DummyModule::HandleInterrupt,//LVD_IRQHandler,
        DummyModule::HandleInterrupt,//TAMPER_IRQHandler,
        DummyModule::HandleInterrupt,//RTC_IRQHandler,
        DummyModule::HandleInterrupt,//FMC_IRQHandler,
        DummyModule::HandleInterrupt,//RCU_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI0_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI1_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI2_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI3_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI4_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel0_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel1_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel2_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel3_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel4_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel5_IRQHandler,
        DummyModule::HandleInterrupt,//DMA0_Channel6_IRQHandler,
        DummyModule::HandleInterrupt,//ADC0_1_IRQHandler,
        DummyModule::HandleInterrupt,//CAN0_TX_IRQHandler,
        DummyModule::HandleInterrupt,//CAN0_RX0_IRQHandler,
        DummyModule::HandleInterrupt,//CAN0_RX1_IRQHandler,
        DummyModule::HandleInterrupt,//CAN0_EWMC_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI5_9_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER0_BRK_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER0_UP_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER0_TRG_CMT_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER0_Channel_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER1_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER2_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER3_IRQHandler,
        DummyModule::HandleInterrupt,//I2C0_EV_IRQHandler,
        DummyModule::HandleInterrupt,//I2C0_ER_IRQHandler,
        DummyModule::HandleInterrupt,//I2C1_EV_IRQHandler,
        DummyModule::HandleInterrupt,//I2C1_ER_IRQHandler,
        DummyModule::HandleInterrupt,//SPI0_IRQHandler,
        DummyModule::HandleInterrupt,//SPI1_IRQHandler,
        DummyModule::HandleInterrupt,//USART0_IRQHandler,
        DummyModule::HandleInterrupt,//USART1_IRQHandler,
        DummyModule::HandleInterrupt,//USART2_IRQHandler,
        DummyModule::HandleInterrupt,//EXTI10_15_IRQHandler,
        DummyModule::HandleInterrupt,//RTC_Alarm_IRQHandler,
        DummyModule::HandleInterrupt,//USBFS_WKUP_IRQHandler,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        DummyModule::HandleInterrupt,//EXMC_IRQHandler,
        nullptr,
        DummyModule::HandleInterrupt,//TIMER4_IRQHandler,
        DummyModule::HandleInterrupt,//SPI2_IRQHandler,
        DummyModule::HandleInterrupt,//UART3_IRQHandler,
        DummyModule::HandleInterrupt,//UART4_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER5_IRQHandler,
        DummyModule::HandleInterrupt,//TIMER6_IRQHandler,
        DummyModule::HandleInterrupt,//DMA1_Channel0_IRQHandler,
        DummyModule::HandleInterrupt,//DMA1_Channel1_IRQHandler,
        DummyModule::HandleInterrupt,//DMA1_Channel2_IRQHandler,
        DummyModule::HandleInterrupt,//DMA1_Channel3_IRQHandler,
        DummyModule::HandleInterrupt,//DMA1_Channel4_IRQHandler,
        nullptr,
        nullptr,
        DummyModule::HandleInterrupt,//CAN1_TX_IRQHandler,
        DummyModule::HandleInterrupt,//CAN1_RX0_IRQHandler,
        DummyModule::HandleInterrupt,//CAN1_RX1_IRQHandler,
        DummyModule::HandleInterrupt,//CAN1_EWMC_IRQHandler,
        DummyModule::HandleInterrupt,//USBFS_IRQHandler
};


struct EnvironmentCall
{
    static void HandleInterrupt()
    {      
      while(true)
      {
        asm volatile(" ");
      }
    }
};
inline constexpr std::array<tInterruptFunction,12> ExceptionVectorTable
{
    DummyModule::HandleInterrupt,  //0 - Instruction address misaligned
    DummyModule::HandleInterrupt,  //1 - Instruction access fault
    DummyModule::HandleInterrupt,  //2 - Illegal instruction
    DummyModule::HandleInterrupt,  //3 - Breakpoint
    DummyModule::HandleInterrupt,  //4 - Load address misaligned
    DummyModule::HandleInterrupt,  //5 - Load access fault
    DummyModule::HandleInterrupt,  //6 - Store/AMO address  misaligned
    DummyModule::HandleInterrupt,  //7 - Store/AMO access fault
    EnvironmentCall::HandleInterrupt,  //8 - Environment call from  U-mode
    nullptr,
    nullptr,
    EnvironmentCall::HandleInterrupt,  //11 - Environment call from  M-mode
};







