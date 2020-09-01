//
// Created by Lamerok on 21.08.2019.
//

#pragma once
#include <cstddef>           //for size_t
#include <type_traits>       //for std::is_base_of, std::is_same
#include "accessmode.hpp"    //for WriteMode, ReadMode
#include "susudefs.hpp"      //for __forceinline
#include "registerfield.hpp" //for RegisterField


//Base class for FieldValue
template<typename Field, typename Base, typename Field::Register::Type value>
struct FieldValueBase
{
  using RegType = typename Field::Register::Type ;
  using FieldType = typename Field::Access ;
  //Method set new value of filed only ofr ReadWrite field
  __forceinline template<
      class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, FieldType>::value>>
  static void Set()
  {
   // static_assert(std::is_base_of<ReadWriteMode, FieldType>::value, "The method is available for ReadWrite register only") ;
    //Read current value of the register
    RegType newRegValue = *reinterpret_cast<volatile RegType *>(Field::Register::Address) ;
    //Clear old value of field
    newRegValue &=~ (Field::Mask << Field::Offset);
    //Set new value
    newRegValue |= (value << Field::Offset) ;
    //Write new value to the field
    *reinterpret_cast<volatile RegType *>(Field::Register::Address) = newRegValue ;
  }


  //Method write the value of register. It can be
  __forceinline template<typename T = typename Field::Access,
          class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value ||
                                            std::is_base_of<ReadWriteMode, T>::value>>
  static void Write()
  {
    *reinterpret_cast<volatile RegType *>(Field::Register::Address) = (value << Field::Offset) ;
  }

  
  //Метод проверяет установлено ли значение битового поля
  __forceinline template<typename T = typename Field::Access,
          class = typename std::enable_if_t<std::is_base_of<ReadMode, T>::value ||
                                            std::is_base_of<ReadWriteMode, T>::value>>
  inline static bool IsSet()
  {
    return ((*reinterpret_cast<volatile RegType *>(Field::Register::Address)) &
              static_cast<RegType>(Field::Mask << Field::Offset)) == (value << Field::Offset) ;
  }
};

