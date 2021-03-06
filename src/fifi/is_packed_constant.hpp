// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

#include "binary.hpp"
#include "binary4.hpp"
#include "binary8.hpp"
#include "binary16.hpp"
#include "prime2325.hpp"

namespace fifi
{
    /// This function determines whether the given constant is packed or not
    ///
    /// if (fifi::is_packed_constant<fifi::binary4>(0xAA))
    /// {
    ///     std::cout << "The constant is correctly packed" << std::endl;
    /// }
    ///
    /// We specialize the is_packed_constant for every field so that
    /// you do not get surprising results when adding new fields.
    /// @param constant Field element to be checked if it is packed or not
    /// @return true if constant is packed, otherwise false
    template<class Field>
    inline bool is_packed_constant(typename Field::value_type constant)
    {
        static_assert(std::is_same<Field, binary8>::value ||
                      std::is_same<Field, binary16>::value ||
                      std::is_same<Field, prime2325>::value,
                      "The generic version is only supported by "
                      "field guaranteed to be packed");

        (void) constant;
        return true;
    }

    /// Specialization for binary
    /// @copydoc is_packed_constant(value_type)
    template<>
    inline bool is_packed_constant<binary>(
        typename binary::value_type constant)
    {
        return constant == 0 || constant == 255;
    }

    /// Specialization for binary4
    /// @copydoc is_packed_constant(value_type)
    template<>
    inline bool is_packed_constant<binary4>(
        typename binary4::value_type constant)
    {
        return ((constant & 0xF0) >> 4) == (constant & 0x0F);
    }

    // /// Specialization for binary8
    // /// @copydoc is_packed_constant(value_type)
    // template<>
    // inline bool is_packed_constant<binary8>(
    //     typename binary8::value_type constant)
    // {
    //     (void) constant;
    //     return true;
    // }

    // /// Specialization for binary16
    // /// @copydoc is_packed_constant(value_type)
    // template<>
    // inline bool is_packed_constant<binary16>(
    //     typename binary16::value_type constant)
    // {
    //     (void) constant;
    //     return true;
    // }

    // /// Specialization for prime2325
    // /// @copydoc is_packed_constant(value_type)
    // template<>
    // inline bool is_packed_constant<prime2325>(
    //     typename prime2325::value_type constant)
    // {
    //     (void) constant;
    //     return true;
    // }
}
