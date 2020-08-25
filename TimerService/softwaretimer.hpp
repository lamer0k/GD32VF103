// Filename: taskertypes.hpp
// Created by Lamerok on 29.03.2020.
#pragma once

template <std::uint32_t TimerFrequency, std::uint32_t msPeriod, typename ... Subscribers>
class SoftwareTimer {
  public:
    static void OnTick()
    {
      --ticksRemain ;
      if (ticksRemain == 0U)
      {       
        ticksRemain = ticksReload ;
        (Subscribers::OnTimeout(),...) ;
      }
    }
    
  private:

    static constexpr std::uint32_t msInSec = 1000UL ;
    static constexpr std::uint32_t ticksReload =  static_cast<std::uint32_t>((msPeriod * TimerFrequency) / msInSec) ;

    static_assert((TimerFrequency <= 10'000U), "System Timer Frequency could not be more than 10 000Hz");
    static_assert((msPeriod <= 400'000U), "msPeriod too big ");

    static_assert((ticksReload != 0UL), "msPeriod too small");
    static inline volatile std::uint32_t ticksRemain = ticksReload;
} ;


