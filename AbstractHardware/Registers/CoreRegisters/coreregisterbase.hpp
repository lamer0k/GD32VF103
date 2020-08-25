//
// Created by Lamerok on 21.08.2019.
//

#pragma once

#include "registertype.hpp"   //for RegisterType
#include "accessmode.hpp"    //for WriteMode, ReadMode
#include "susudefs.hpp"      //for __forceinline

//Базовый класс для работы с регистром
template<std::uintptr_t address, size_t size, typename AccessMode>
struct CoreRegisterBase
{
  static constexpr auto Address = address ;
  using Type = typename RegisterType<size>::Type ;


  //Метод Write будет работать только для регистров, в которые можно записать значение
  __forceinline template<typename T = AccessMode,
    class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value || std::is_base_of<ReadWriteMode, T>::value >>
  inline static void Write(Type value)
  {
    __write_csr(address, value) ;
  }

    //Метод Write будет работать только для регистров, в которые можно записать значение
    __forceinline template<Type value, typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value || std::is_base_of<ReadWriteMode, T>::value >>
    inline static void Write()
    {
        __write_csr(address, value) ;
    }

  //Метод Write будет работать только для регистров, в которые можно записать значение
  __forceinline template<typename T = AccessMode,
      class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value || std::is_base_of<ReadWriteMode, T>::value >>
  inline static void Set(Type value)
  {
     Type oldRegValue = __read_csr(address);  //Сохраняем текущее значение регистра 
    __write_csr(address, (oldRegValue | value)) ;
  }

    //Метод Write будет работать только для регистров, в которые можно записать значение
    __forceinline template<Type value, typename T = AccessMode,
        class = typename std::enable_if_t<std::is_base_of<WriteMode, T>::value || std::is_base_of<ReadWriteMode, T>::value >>
    inline static void Set()
    {
        Type oldRegValue = __read_csr(address);  //Сохраняем текущее значение регистра
        __write_csr(address, (oldRegValue | value)) ;
    }


    //Метод Write будет работать только для регистров, в которые можно записать значение
  __forceinline template<typename T = AccessMode,
    class = typename std::enable_if_t<std::is_base_of<ReadWriteMode, T>::value>>
  inline static void Toggle(Type value)
  {
      Type regValue = __read_csr(address);  //Сохраняем текущее значение регистра
      regValue ^= value;
      __write_csr(address, regValue) ;

  }

  //Метод Get возвращает целое значение регистра, будет работать только для регистров, которые можно считать
  __forceinline template<typename T = AccessMode,
          class = typename std::enable_if_t<std::is_base_of<ReadMode, T>::value ||
                                            std::is_base_of<ReadWriteMode, T>::value>>
  inline static Type Get()
  {
    return __read_csr(address) ;
  }
} ;


