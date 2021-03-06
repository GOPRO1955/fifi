// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_info.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/expected_results.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack : public region_info<final<Field> >
        { };
    }
}

template<class Field>
void test_region_alignment()
{
    EXPECT_EQ(sizeof(typename Field::value_type),
              fifi::dummy_stack<Field>().alignment());
}

template<class Field>
void test_region_max_alignment()
{
    EXPECT_EQ(sizeof(typename Field::value_type),
              fifi::dummy_stack<Field>().max_alignment());
}

template<class Field>
void test_region_granularity()
{
    EXPECT_EQ(1U, fifi::dummy_stack<Field>().granularity());
}

template<class Field>
void test_region_max_granularity()
{
    EXPECT_EQ(1U, fifi::dummy_stack<Field>().max_granularity());
}


TEST(test_region_info, alignment)
{
    {
        SCOPED_TRACE("binary");
        test_region_alignment<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        test_region_alignment<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        test_region_alignment<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        test_region_alignment<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        test_region_alignment<fifi::prime2325>();
    }
}

TEST(test_region_info, max_alignment)
{
    {
        SCOPED_TRACE("binary");
        test_region_max_alignment<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        test_region_max_alignment<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        test_region_max_alignment<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        test_region_max_alignment<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        test_region_max_alignment<fifi::prime2325>();
    }
}

TEST(test_region_info, granularity)
{
    {
        SCOPED_TRACE("binary");
        test_region_granularity<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        test_region_granularity<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        test_region_granularity<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        test_region_granularity<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        test_region_granularity<fifi::prime2325>();
    }
}

TEST(test_region_info, max_granularity)
{
    {
        SCOPED_TRACE("binary");
        test_region_max_granularity<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        test_region_max_granularity<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        test_region_max_granularity<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        test_region_max_granularity<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        test_region_max_granularity<fifi::prime2325>();
    }
}
