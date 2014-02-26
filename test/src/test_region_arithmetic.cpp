// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/region_info.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_fall_through.hpp"

#include <tuple>

class arguments
{
    virtual bool compare();
};


namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        // Dummy stack used to check the fall-through
        template<class Field>
        struct dummy_stack : public
            region_arithmetic<
            helper_fall_through<Field> >
        { };
    }
}

TEST(TestRegionArithmetic, fall_through)
{
    typedef fifi::binary8 field_type;
    typedef field_type::value_type value_type;
    typedef fifi::dummy_stack<field_type> stack;

    value_type dest[2] = {0xf0, 0x0f};
    value_type src[2] = {0xab, 0xba};
    value_type constant = fifi::pack<field_type>(1U);

    uint32_t length = 2;

    fifi::capture_calls<value_type> expected_calls;

    stack s;

    // Add
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_packed_add(dest[0],src[0]);
    expected_calls.call_packed_add(dest[1],src[1]);

    s.region_add(dest, src, length);

    expected_calls.return_packed_add(dest[0]);
    expected_calls.return_packed_add(dest[1]);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Subtract
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_packed_subtract(dest[0],src[0]);
    expected_calls.call_packed_subtract(dest[1],src[1]);

    s.region_subtract(dest, src, length);

    expected_calls.return_packed_subtract(dest[0]);
    expected_calls.return_packed_subtract(dest[1]);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Divide
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_packed_divide(dest[0],src[0]);
    expected_calls.call_packed_divide(dest[1],src[1]);

    s.region_divide(dest, src, length);

    expected_calls.return_packed_divide(dest[0]);
    expected_calls.return_packed_divide(dest[1]);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Multiply
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_packed_multiply(dest[0],src[0]);
    expected_calls.call_packed_multiply(dest[1],src[1]);

    s.region_multiply(dest, src, length);

    expected_calls.return_packed_multiply(dest[0]);
    expected_calls.return_packed_multiply(dest[1]);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Multiply Constant
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_packed_multiply(dest[0], constant);
    expected_calls.call_packed_multiply(dest[1], constant);

    s.region_multiply_constant(dest, constant, length);

    expected_calls.return_packed_multiply(dest[0]);
    expected_calls.return_packed_multiply(dest[1]);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Multiply Add

    s.m_calls.clear();
    expected_calls.clear();

    // Access the constants generated by the test stack, we advance
    // our constant generator at the same pace as the test stack so we
    // can "predict" the values added together.
    auto constants = s.m_constants;

    // We have 4 function calls so we will have 4 expected returns
    value_type expected_return[4] = { constants.pack(), constants.pack(),
                                      constants.pack(), constants.pack() };

    expected_calls.call_packed_multiply(src[0], constant);
    expected_calls.return_packed_multiply(expected_return[0]);

    expected_calls.call_packed_add(dest[0], expected_return[0]);
    expected_calls.return_packed_add(expected_return[1]);

    expected_calls.call_packed_multiply(src[1], constant);
    expected_calls.return_packed_multiply(expected_return[2]);

    expected_calls.call_packed_add(dest[1], expected_return[2]);
    expected_calls.return_packed_add(expected_return[3]);

    s.region_multiply_add(dest, src, constant, length);

    EXPECT_EQ(expected_calls, s.m_calls);

    // The call to the packed_add should end up in dest
    EXPECT_EQ(dest[0], expected_return[1]);
    EXPECT_EQ(dest[1], expected_return[3]);


    // Multiply subtract

    s.m_calls.clear();
    expected_calls.clear();

    // Access the constants generated by the test stack, we advance
    // our constant generator at the same pace as the test stack so we
    // can "predict" the values added together.
    constants = s.m_constants;

    // We have 4 function calls so we will have 4 expected returns
    value_type multiply_subtract_return[4] =
        { constants.pack(), constants.pack(),
          constants.pack(), constants.pack() };

    expected_calls.call_packed_multiply(src[0], constant);
    expected_calls.return_packed_multiply(multiply_subtract_return[0]);

    expected_calls.call_packed_subtract(dest[0], multiply_subtract_return[0]);
    expected_calls.return_packed_subtract(multiply_subtract_return[1]);

    expected_calls.call_packed_multiply(src[1], constant);
    expected_calls.return_packed_multiply(multiply_subtract_return[2]);

    expected_calls.call_packed_subtract(dest[1], multiply_subtract_return[2]);
    expected_calls.return_packed_subtract(multiply_subtract_return[3]);

    s.region_multiply_subtract(dest, src, constant, length);

    EXPECT_EQ(expected_calls, s.m_calls);

    // The call to the packed_add should end up in dest
    EXPECT_EQ(dest[0], multiply_subtract_return[1]);
    EXPECT_EQ(dest[1], multiply_subtract_return[3]);
}


