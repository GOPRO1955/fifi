// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary8.hpp>

#include <gtest/gtest.h>

TEST(test_binary8, binary8)
{
    EXPECT_EQ(255U, fifi::binary8::max_value);
    EXPECT_EQ(0U, fifi::binary8::min_value);
    EXPECT_EQ(256U, fifi::binary8::order);
    EXPECT_EQ(8U, fifi::binary8::degree);
    EXPECT_EQ(29U, fifi::binary8::prime);
    EXPECT_TRUE(fifi::binary8::is_exact);
}
