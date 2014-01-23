// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/full_table.hpp>
#include <fifi/field_types.hpp>

#include "expected_results.hpp"

template<class Field>
inline void test_full_table()
{
    check_results_multiply<fifi::full_table<Field> >();
    check_results_invert<fifi::full_table<Field> >();
    check_results_divide<fifi::full_table<Field> >();
    check_results_add<fifi::full_table<Field> >();
    check_results_subtract<fifi::full_table<Field> >();
    check_random<fifi::full_table<Field> >();
}

TEST(TestFullTable, api)
{
   test_full_table<fifi::binary4>();
   test_full_table<fifi::binary8>();
}
