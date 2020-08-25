// Filename: softwaretimerconfig.hpp
// Created Kolody  on 10.08.2020.
#pragma once

#include "TimerService/timerservice.hpp" // for TimerService
#include "TimerService/softwaretimer.hpp" //
#include "systemconfig.hpp" // for SystemTimerPeriod
#include "leds.hpp" // for Led1, Led2, Led3, Led4


using Led1Timer = SoftwareTimer<SystemTimerPeriod, 100UL, Led1> ;
using Led2Timer = SoftwareTimer<SystemTimerPeriod, 200UL, Led2> ;
//using Led3Timer = SoftwareTimer<SystemTimerPeriod, 300UL, Led3> ;
//using Led4Timer = SoftwareTimer<SystemTimerPeriod, 400UL, Led4> ;

using AppTimerService = TimerService<Led1Timer, Led2Timer> ;