// Filename: corevaluebits.hpp
// Created by by Sergey Kolody  on 09.08.2020.

#pragma once
#include "accessmode.hpp"    //for WriteMode, ReadMode
#include <type_traits>       //for std::is_base_of, std::is_same
#include "susudefs.hpp"      //for __forceinline

//Базовый класс для работы с битовыми полями регистров
template<typename Field, typename Base, typename Field::Register::Type value>
struct CoreFieldValueMask
{
    using RegType = typename Field::Register::Type ;
    //Метод устанавливает значение битового поля, только в случае, если оно достпуно для записи
    __forceinline template<typename T = typename Field::Access,
        class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, T>::value>>
    static void Set()
    {
        __set_bits_csr(Field::Register::Address, (value << Field::Offset)) ;
    }


    __forceinline template<typename T = typename Field::Access,
        class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, T>::value>>
    static void Clear()
    {
        __clear_bits_csr(Field::Register::Address, (value << Field::Offset)) ;
    }


    //Метод проверяет установлено ли значение битового поля
    __forceinline template<typename T = typename Field::Access,
        class = typename std::enable_if_t<std::is_base_of<ReadMode, T>::value ||
                                          std::is_base_of<ReadWriteMode, T>::value>>
    inline static bool IsSet()
    {
        RegType oldRegValue = __read_csr(Field::Register::Address);  //Сохраняем текущее значение регистра
        return (oldRegValue & static_cast<RegType>(Field::Mask << Field::Offset)) == (value << Field::Offset) ;
    }
};

