//
// Created by SKolody on 08.07.2020.
//
#pragma once

#include <cassert>      //for assert
#include "susudefs.hpp" //for __forceinline (#define __forceinline  _Pragma("inline=forced"))
#include <limits>       //for std::numeric_limits

//Базовый класс для работы с битовыми полями регистров
template<typename Reg, size_t offset, size_t size, typename AccessMode>
struct CoreRegisterField
{
    using RegType = typename Reg::Type;
    using Register = Reg;

    static constexpr RegType Offset = offset;
    static constexpr RegType Size = size;
    static constexpr RegType Mask = (size < sizeof(RegType) * 8U) ? (static_cast<RegType>(
        (static_cast<RegType>(1U) << size) - static_cast<RegType>(1U))) : std::numeric_limits<RegType>::max();
    using Access = AccessMode;

    //Метод устанавливает значение битового поля, только в случае, если оно достпуно для записи
    __forceinline template<typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, T>::value>>
    static void Set(RegType value)
    {
        assert(value < (1U << (size - 1)));

        RegType newRegValue = __read_csr(Reg::Address);
        newRegValue &= ~(Mask << offset); //Вначале нужно очистить старое значение битового поля
        newRegValue |= (value << offset); // Затем установить новое
        __write_csr(Reg::Address, newRegValue);
    }

    //Метод устанавливает значение битового поля, только в случае, если оно достпуно для записи
    __forceinline template<RegType value, typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, T>::value>>
    static void Set()
    {
        static_assert((value < (1U << (size - 1))), "Value type size is more then the field size");

        RegType newRegValue = __read_csr(Reg::Address);

        newRegValue &= ~(Mask << offset); //Вначале нужно очистить старое значение битового поля
        newRegValue |= (value << offset); // Затем установить новое

        __write_csr(Reg::Address, newRegValue);
    }


    //Метод устанавливает значение битового поля, только в случае, если оно доступно для записи
    __forceinline template<typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value ||
                                          std::is_base_of<ReadWriteMode, T>::value>>
    static void Write(RegType value)
    {
        assert(value < (1U << (size - 1)));
        __write_csr(Reg::Address, (value << offset));
    }

    //Метод устанавливает значение битового поля, только в случае, если оно доступно для записи
    __forceinline template<RegType value, typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value ||
                                          std::is_base_of<ReadWriteMode, T>::value>>
    static void Write()
    {
        static_assert((value < (1U << (size - 1))), "Value type size is more then the field size");
        __write_csr(Reg::Address, (value << offset));
    }

    //Метод устанавливает проверяет установлено ли значение битового поля
    __forceinline template<typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<ReadMode, T>::value ||
                                          std::is_base_of<ReadWriteMode, T>::value>>
    inline static RegType Get()
    {
        volatile RegType oldRegValue = __read_csr(Reg::Address);  //Сохраняем текущее значение регистра
        return (oldRegValue & ((Mask << offset))) >> offset;
    }
};
