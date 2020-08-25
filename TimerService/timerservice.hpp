// Filename: taskertypes.hpp
// Created by by Sergey Kolody aka Lamerok on 29.03.2020.
#pragma once



template<typename ...Timers>
struct TimerService
{
    static void OnSystemTick()
    {
        (Timers::OnTick(), ...);
    }
};

