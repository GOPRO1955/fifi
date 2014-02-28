// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/full_table_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_fall_through.hpp"

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        template<class Field>
        struct dummy_stack_fall_through : public
            full_table_arithmetic<
            helper_fall_through<Field> >
        { };

        template<class Field>
        struct dummy_stack : public
            full_table_arithmetic<
            simple_online_arithmetic<
            polynomial_degree<
            final<Field> > > >
        { };
    }
}

template<class Field>
inline void helper_fall_through()
{
    typedef fifi::dummy_stack_fall_through<Field> stack;

    fifi::capture_calls<typename Field::value_type> expected_calls;
    stack s;

    s.m_calls.clear();
    expected_calls.clear();
    s.multiply(1, 1);
    s.divide(1, 1);
    s.invert(1);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Test that other calls does fall through.
    fifi::test_fall_through_add<stack>();
    fifi::test_fall_through_subtract<stack>();
}

TEST(TestFullTableArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary4");
        helper_fall_through<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        helper_fall_through<fifi::binary8>();
    }
}

TEST(TestFullTableArithmetic, multiply)
{
    {
        SCOPED_TRACE("binary4");
        check_results_multiply<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_multiply<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(TestFullTableArithmetic, divide)
{
    {
        SCOPED_TRACE("binary4");
        check_results_divide<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_divide<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(TestFullTableArithmetic, invert)
{
    {
        SCOPED_TRACE("binary4");
        check_results_invert<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_invert<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(TestFullTableArithmetic, random)
{
    {
        SCOPED_TRACE("binary4");
        check_random_default<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_random_default<fifi::dummy_stack<fifi::binary8> >();
    }
}
