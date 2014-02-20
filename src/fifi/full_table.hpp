// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary4.hpp"
#include "binary4_packed_arithmetic.hpp"
#include "binary8_region_arithmetic_full_table.hpp"
#include "final.hpp"
#include "full_table_arithmetic.hpp"
#include "packed_arithmetic.hpp"
#include "polynomial_degree.hpp"
#include "region_arithmetic.hpp"
#include "region_info.hpp"
#include "simple_online_arithmetic.hpp"
#include "region_dispatcher.hpp"
#include "ssse3_binary4_full_table.hpp"
#include "correct_alignment.hpp"
#include "correct_granularity.hpp"
#include "name_super.hpp"

namespace fifi
{
    /// The full look-up table stack. This stack does most
    /// computations base on full look-up tables.
    template<class Field>
    class full_table :
        public correct_alignment<
               correct_granularity<
               helper_region<ssse3_binary4_full_table,
               name_super<
               binary8_region_arithmetic_full_table<Field,
               region_arithmetic<
               region_info<
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               full_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > > > > > > >
    { };
}
