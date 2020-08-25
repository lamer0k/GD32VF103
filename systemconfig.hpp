// Filename: systemconfig.hpp
// Created Lamerok  on 10.08.2020.

#pragma once

#include <cstdint> // For std::uint32_t

constexpr std::uint32_t SystemCoreClock = 8'000'000U; //Hz
constexpr std::uint32_t SystemTimerSourceFrequency = SystemCoreClock/4U;  //HZ
inline constexpr std::uint32_t SystemTimerPeriod = SystemTimerSourceFrequency / 1000;





