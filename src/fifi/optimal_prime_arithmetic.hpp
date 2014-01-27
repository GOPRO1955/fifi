// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include "prime2325.hpp"

namespace fifi
{
    /// Fall through case for other fields(?)
    template<class Field>
    class optimal_prime_arithmetic
    { };

    /// This implementation allows finite field arithmetics in the
    /// prime fields in this case where the characteristic of the
    /// field is different than two.
    template<>
    class optimal_prime_arithmetic<prime2325>
    {
    public:
        /// Typedef of the data type used for each field element
        typedef typename prime2325::value_type value_type;

        /// Typedef of the field type used
        typedef prime2325 field_type;

    public:
        /// Specialization for the (2^32 - 5) prime field. Multiplication is
        /// based on a clever way of doing modulo. See:
        ///
        ///   S. B. Mohan  and  B. S. Adiga, Electronics  “Fast algorithms for
        ///   implementing rsa public key cryptosystem" Electronics  Letters,
        ///   vol.  21, 1985.
        value_type multiply(value_type element_one,
                                           value_type element_two) const
        {
            uint64_t c = static_cast<uint64_t>(element_one) *
                         static_cast<uint64_t>(element_two);

            uint32_t l1 = c & 0xffffffff;
            c = c >> 32;
            c = c * 5;

            uint32_t l2 = c & 0xffffffff;
            c = c >> 32;
            c = c * 5;

            c = c + l1 + l2;

            c = c >= prime2325::prime ? c - prime2325::prime : c;

            return static_cast<value_type>(c);

        }

        /// Specialization for the (2^32 - 5) prime field. In this case division is
        /// simply implemented using multiplication with the inverse.
        value_type divide(value_type numerator, value_type denominator) const
        {
            value_type inverse = invert(denominator);
            return multiply(numerator, inverse);
        }

        /// Specialization for the (2^32 - 5) prime field. This algorithm used a
        /// modified version of the Extended Euclidean algorithm, which essentially
        /// solves the a*x + b*y = gcd(a,b) in this case b = 2^32 - 5 which is a
        /// prime therefore we know that gcd(a,b) = 1 also since we do all
        /// calculations mod 2^32 - 5 we see that b*y must become 0. We are left
        /// with calculating a*x = 1 in which case x must be the inverse of a.
        value_type invert(value_type element) const
        {
            assert(element > 0);
            assert(element < prime2325::prime);

            int64_t q  = 0;

            int64_t x  = 0;
            int64_t x0 = 0;
            int64_t x1 = 1;

            int64_t r  = 0;
            int64_t r0 = prime2325::prime;
            int64_t r1 = element;

            while(r1 != 1)
            {
                // Compute the next remainder
                q = r0 / r1;
                r = r0 - (q * r1);
                x = x0 - (q * x1);

                // Store the results
                r0 = r1;
                r1 = r;
                x0 = x1;
                x1 = x;
            }

            x1 = x1 < 0 ? (x1 + prime2325::prime) : x1;

            return static_cast<value_type>(x1);
        }

        /// Specialization for the (2^32 - 5) prime field
        value_type add(value_type element_one, value_type element_two) const
        {
            element_one = element_one + element_two;
            element_one = element_one + (5 & ((element_one >= element_two) - 1));


            element_one = element_one -
                (prime2325::prime & ((prime2325::prime > element_one) - 1));

            return element_one;
        }

        /// Specialization for the (2^32 - 5) prime field
        value_type subtract(value_type element_one, value_type element_two) const
        {
            // Se explanation for the funny business below in arithmetics.h
            // specialization of subtract for optimal_prime<prime2325>
            return (element_one - element_two)
                + (-5 & ((element_one >= element_two) - 1));
        }
    };
}