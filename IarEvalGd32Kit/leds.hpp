// Filename: leds.hpp
// Created by by Sergey Kolody  on 10.08.2020.

#pragma once

#include "gpiocregisters.hpp"
#include "gpiobregisters.hpp"
#include <iostream>

template<typename Pin>
struct Leds
{
    static void OnTimeout()
    {
        Pin::Toggle();
    }
};

template<typename Port, uint32_t num>
struct DummyPin
{
    static void Toggle()
    {
        Port::OCTL::Toggle(1 << num);
    }
};

using Led1 = Leds<DummyPin<GPIOC, 7>>;
using Led2 = Leds<DummyPin<GPIOB, 6>>;
//using Led3 = Leds<DummyPin<2>>;
//using Led4 = Leds<DummyPin<3>>;