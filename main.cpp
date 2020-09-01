#include "gpiocregisters.hpp"
#include "gpiobregisters.hpp"
#include "rcuregisters.hpp"  //for RCU
#include "csrregisters.hpp" //for CSR
#include "eclicregisters.hpp" // for ECLIC
#include "machinetimerregisters.hpp"
#include "systemconfig.hpp" // for SystemTimerPeriod
#include "criticalsection.hpp" // for CriticalSection
#include "csrcustomregisters.hpp"
#include "vectortable.hpp" //for InterruptVectorTable

namespace NonVectoredInt
{
    static void HandleInterrupt(std::uint32_t interruptId)
    {
        assert(interruptId < InterruptVectorTable.size());
        tInterruptFunction fp = InterruptVectorTable[interruptId];
        if (fp != nullptr)
        {
            fp();
        }
    }

    static void HandleException(std::uint32_t exceptiontId)
    {
        assert(exceptiontId < ExceptionVectorTable.size());
        tInterruptFunction fp = ExceptionVectorTable[exceptiontId];
        if (fp != nullptr)
        {
            fp();
        }
    }

    __interrupt void ExceptionEntry()
    {
        const auto mcause = CSR::MCAUSE::Get();
        const auto mepc = CSR::MEPC::Get();
        const auto msubm = CSRCUSTOM::MSUBM::Get();
        const auto exceptionCode = mcause & 0xFFF;

        if (exceptionCode != 0xFFF) // if not NMI
        {
            NonVectoredInt::HandleException(exceptionCode);
        }
        else
        {
            DummyModule::HandleInterrupt(); // for NMI handling
        }

        __disable_interrupt();
        CSR::MCAUSE::Write(mcause);
        CSR::MEPC::Write(mepc);
        CSRCUSTOM::MSUBM::Write(msubm);
    }

    __interrupt void IrqEntry()
    {
        const auto mcause = CSR::MCAUSE::Get();
        const auto mepc = CSR::MEPC::Get();
        const auto msubm = CSRCUSTOM::MSUBM::Get();
        const auto exceptionCode = mcause & 0xFFF;

        NonVectoredInt::HandleInterrupt(exceptionCode);

        __disable_interrupt();
        CSR::MCAUSE::Write(mcause);
        CSR::MEPC::Write(mepc);
        CSRCUSTOM::MSUBM::Write(msubm);
    }
}

extern "C"
{
int __low_level_init(void)
{
    {
        CriticalSection cs;

        // Устанавливаем указание адреса обработчика NMI через общий обработчик,
        // адрес которого указан в mtvec. Номер обработчика NMI будт 0xFFF
        CSRCUSTOM::MMISC_CTL::NMI_CAUSE_FFF::MnvecIsMtvecNmiIsFFF::Set();

        // Настраиваем адрес единого обработчика прерываний.
        // Указываем, что он будет находится в регистре MTVT2
        CSRCUSTOM::MTVT2::Write(CSRCUSTOM::MTVT2::MTVT2EN::Mtvt2IsTrapAddress::Value |
                                reinterpret_cast<std::uintptr_t>(&NonVectoredInt::IrqEntry));

        // Переключаемся на режим работы с ECLIC и устанавливаем
        // адрес единого обработчика исключений
        CSR::MTVEC::Write(CSR::MTVEC::MODE::Eclic::Value |
                          reinterpret_cast<std::uintptr_t>(&NonVectoredInt::ExceptionEntry));

        // Включаем подсчет циклов и счетчика инструкций mycycle_minstret
        CSRCUSTOM::MCOUNTINHIBITPack<CSRCUSTOM::MCOUNTINHIBIT::IR::MinstretOn,
                                     CSRCUSTOM::MCOUNTINHIBIT::CY::McyclesOn
        >::Set();
    }
    ECLIC::CLICCFG::NLBITS::MaxBitsForLevel3::Set();

    //Ставим уровень срабатывания прерывания в 0
    ECLIC::MTH::Write(0U);
    //Ставим невекторный режим для обработки прерывания таймера
    ECLIC::CLICINTATTR_7::SHV::NonVectored::Set();

    //Ставим уровень прерывания в 1, приоритет не будем трогать
    ECLIC::CLICINTCTL_7::Write<1U << (8U - ECLIC::CLICCFG::NLBITS::MaxBitsForLevel3::Value)>();

    MACHINETIMER::MTIMECMP::MTIMECMPField::Value<SystemTimerPeriod>::Write();
    MACHINETIMER::MTIME::Write<0U>();

    //Разрешить прерывание таймера - прерывание номер 7
    ECLIC::CLICINTIE_7::IE::Enable::Write();

    //Enable machine interrupt
    CSR::MSTATUSPack<CSR::MSTATUS::MIE::InterruptEnabled>::SetValueBits();

    RCU::APB2ENPack<RCU::APB2EN::PCEN::Enable,
                    RCU::APB2EN::PBEN::Enable>::Set();
    GPIOC::CTL0::CTLMD7::GpioOutputPushPull50Mhz::Set();
    GPIOB::CTL0::CTLMD6::GpioOutputPushPull50Mhz::Set();

    return 1;
}
}

int main()
{
    while (true)
    {
        asm volatile(" ");
    }

    return 0;
}
