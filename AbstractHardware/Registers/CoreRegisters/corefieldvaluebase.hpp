//
// Created by Lamerok on 21.08.2019.
//
#pragma once

#include <cstddef>           //for size_t
#include <type_traits>       //for std::is_base_of, std::is_same
#include "accessmode.hpp"    //for WriteMode, ReadMode
#include "susudefs.hpp"      //for __forceinline
#include "coreregisterfield.hpp" //for RegisterField


//Базовый класс для работы с битовыми полями регистров
template<typename Field, typename Base, typename Field::Register::Type value>
struct CoreFieldValueBase
{
  using RegType = typename Field::Register::Type ;
  //Метод устанавливает значение битового поля, только в случае, если оно достпуно для записи
  __forceinline template<typename T = typename Field::Access,
          class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, T>::value>>
  static void Set()
  {
    RegType newRegValue = __read_csr(Field::Register::Address);  //Сохраняем текущее значение регистра

    newRegValue &=~ (Field::Mask << Field::Offset); //Вначале нужно очистить старое значение битового поля
    newRegValue |= (value << Field::Offset) ; // Затем установить новое

    __write_csr(Field::Register::Address, newRegValue) ;
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

