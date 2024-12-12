// Copyright (C) 2024 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <algorithm>

export module br.dev.pedrolamarao.fm2gp;

export namespace br::dev::pedrolamarao::fm2gp
{
    auto is_even (unsigned x) -> bool
    {
        return (x & 1) == 0;
    }

    auto is_odd (unsigned x) -> bool
    {
        return (x & 1) == 1;
    }

    auto is_equal (unsigned x, unsigned y) -> bool
    {
        return x == y;
    }

    auto not_equal (unsigned x, unsigned y) -> bool
    {
        return x != y;
    }

    auto is_less (unsigned x, unsigned y) -> bool
    {
        return x < y;
    }

    auto not_less (unsigned x, unsigned y) -> bool
    {
        return x >= y;
    }

    auto not_greater (unsigned x, unsigned y) -> bool
    {
        return x <= y;
    }

    auto sum (unsigned x, unsigned y) -> unsigned
    {
        return x + y;
    }

    auto difference (unsigned x, unsigned y) -> unsigned
    {
        return x - y;
    }

    auto half (unsigned x) -> unsigned
    {
        return x >> 1;
    }

    auto twice (unsigned x) -> unsigned
    {
        return x << 1;
    }

    // Chapter 2: The First Algorithm

    // requires: n > 0
    auto multiply_0 (unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return x;
        else return x + multiply_0( x, n - 1 );
    }

    // requires: n > 0
    auto multiply_1 (unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return x;
        unsigned r = multiply_1( x + x, half(n) );
        if (is_odd(n)) r = r + x;
        return r;
    }

    // requires: n > 0
    auto multiply_accumulate_0 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (n == 1)           return r + x;
        else if (is_odd(n))   return multiply_accumulate_0( r + x, x + x, half(n) );
        else /* is_even(n) */ return multiply_accumulate_0( r, x + x, half(n) );
    }

    // requires: n > 0
    auto multiply_accumulate_1 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return r + x;
        if (is_odd(n)) r = r + x;
        return multiply_accumulate_1( r, x + x, half(n) );
    }

    // requires: n > 0
    auto multiply_accumulate_2 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (is_odd(n)) {
            r = r + x;
            if (n == 1) return r;
        }
        return multiply_accumulate_2( r, x + x, half(n) );
    }

    // requires: n > 0
    auto multiply_accumulate_3 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (is_odd(n)) {
            r = r + x;
            if (n == 1) return r;
        }
        x = x + x;
        n = half(n);
        return multiply_accumulate_2( r, x, n );
    }

    // requires: n > 0
    auto multiply_accumulate_4 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        while (true) {
            if (is_odd(n)) {
                r = r + x;
                if (n == 1) return r;
            }
            x = x + x;
            n = half(n);
        }
    }

    // requires: n > 0
    auto multiply_2 (unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return x;
        return multiply_accumulate_4(x, x, n - 1);
    }

    // requires: n > 0
    auto multiply_3 (unsigned x, unsigned n) -> unsigned
    {
        while (! is_odd(n)) {
            x = x + x;
            n = half(n);
        }
        if (n == 1) return x;
        return multiply_accumulate_4(x, x, n - 1);
    }

    // requires: n > 0
    auto multiply_4 (unsigned x, unsigned n) -> unsigned
    {
        while (! is_odd(n)) {
            x = x + x;
            n = half(n);
        }
        if (n == 1) return x;
        return multiply_accumulate_4(x, x + x, half(n - 1));
    }

    // bonus

    template <typename O>
    concept BiOperator = requires (O o, unsigned x, unsigned y, unsigned z)
    {
        z = o(x,y);
    };

    // requires: n > 0
    auto power_accumulate_4 (BiOperator auto o, unsigned r, unsigned x, unsigned n) -> unsigned
    {
        while (true) {
            if (is_odd(n)) {
                r = o(r,x);
                if (n == 1) return r;
            }
            x = o(x,x);
            n = half(n);
        }
    }

    // requires: n > 0
    auto power_4 (BiOperator auto o, unsigned x, unsigned n) -> unsigned
    {
        while (! is_odd(n)) {
            x = o(x,x);
            n = half(n);
        }
        if (n == 1) return x;
        return power_accumulate_4(o, x, o(x,x), half(n-1));
    }

    auto multiply_power_4 (unsigned x, unsigned n) -> unsigned
    {
        return power_4(sum, x, n);
    }

    // Chapter 3: Ancient Greek Number Theory

    template <typename T>
    concept RandomAccessIterator = true;

    template <typename T>
    concept Integer = true;

    // requires: first != last
    template <RandomAccessIterator Iterator>
    void mark_sieve (Iterator first, Iterator last, Integer auto factor)
    {
        *first = false;
        while (last - first > factor) {
            first = first + factor;
            *first = false;
        }
    }

    template <RandomAccessIterator I, Integer N>
    void sift_0 (I first, N n)
    {
        std::fill_n(first, n, true);
        N i { 0 };
        N index_square { 3 };
        while (index_square < n) {
            // invariant: index_square = 2i^2 + 6i + 3
            if (first[i]) {
                // if candidate is prime
                mark_sieve(first + index_square,
                first + n, // last
                i + i + 3); // factor
            }
            ++i;
            index_square = 2*i*(i + 3) + 3;
        }
    }

    template <RandomAccessIterator I, Integer N>
    void sift_1 (I first, N n)
    {
        I last = first + n;
        std::fill(first, last, true);
        N i { 0 };
        N index_square { 3 };
        N factor { 3 };
        while (index_square < n) {
            // invariant: index_square = 2i^2 + 6i + 3,
            //            factor = 2i + 3;
            if (first[i]) {
                mark_sieve(first + index_square, last, factor);
            }
            ++i;
            factor = i + i + 3;
            index_square = 2 * i * (i + 3) + 3;
        }
    }

    template <RandomAccessIterator I, Integer N>
    void sift_2 (I first, N n)
    {
        constexpr N two { 2 };
        I last = first + n;
        std::fill(first, last, true);
        N i { 0 };
        N index_square { 3 };
        N factor { 3 };
        while (index_square < n) {
            // invariant: index_square = 2i^2 + 6i + 3,
            //            factor = 2i + 3;
            if (first[i]) {
                mark_sieve(first + index_square, last, factor);
            }
            ++i;
            index_square = index_square + factor;
            factor = factor + two;
            index_square = index_square + factor;
        }
    }

    // requires: x > 0, y > 0
    auto gcm (unsigned x, unsigned y) -> unsigned
    {
        if (is_equal(x,y))     return x;
        else if (is_less(x,y)) return gcm(x,difference(y,x));
        else                   return gcm(difference(x,y), y);
    }

    // Chapter 4: Euclid's Algorithm

    // requires: x > 0, y > 0
    auto gcm_0 (unsigned x, unsigned y) -> unsigned
    {
        while (not_equal(x,y)) {
            if (is_less(x,y)) y = difference(y,x);
            else              x = difference(x,y);
        }
        return x;
    }

    // requires: x > 0, y > 0
    auto gcm_1 (unsigned x, unsigned y) -> unsigned
    {
        while (not_equal(x,y)) {
            while (is_less(y,x)) x = difference(x,y);
            std::swap(x,y);
        }
        return x;
    }

    // requires: x > 0, y > 0
    auto remainder_0 (unsigned x, unsigned y) -> unsigned
    {
        while (is_less(y,x)) x = difference(x,y);
        return x;
    }

    // requires: x > 0, y > 0
    auto gcm_2 (unsigned x, unsigned y) -> unsigned
    {
        while (not_equal(x,y)) {
            x = remainder_0(x,y);
            std::swap(x,y);
        }
        return x;
    }

    // requires: x > 0, y > 0
    auto remainder_1 (unsigned x, unsigned y) -> unsigned
    {
        if (not_greater(x,y)) return x;
        if (not_greater(difference(x,y),y)) return difference(x,y);
        x = remainder_1(x,twice(y));
        if (not_greater(x,y)) return x;
        return x - y;
    }

    // requires: x > 0, y > 0
    auto gcm_3 (unsigned x, unsigned y) -> unsigned
    {
        while (not_equal(x,y)) {
            x = remainder_1(x,y);
            std::swap(x,y);
        }
        return x;
    }

    // requires: y > 0
    auto remainder_2 (unsigned x, unsigned y) -> unsigned
    {
        if (is_less(x,y)) return x;
        if (is_less(difference(x,y),y)) return difference(x,y);
        x = remainder_1(x,twice(y));
        if (is_less(x,y)) return x;
        return difference(x,y);
    }

    // requires: y > 0
    auto largest_doubling (unsigned x, unsigned y) -> unsigned
    {
        while (not_less(difference(x,y),y)) y = twice(y);
        return y;
    }

    // requires: y > 0
    auto remainder_3 (unsigned x, unsigned y) -> unsigned
    {
        if (is_less(x,y)) return x;
        auto z = largest_doubling(x,y);
        x = difference(x,z);
        while (not_equal(z,y)) {
            z = half(z);
            if (not_greater(z,x)) x = difference(x,z);
        }
        return x;
    }

    // requires: y > 0
    auto quotient_3 (unsigned x, unsigned y) -> unsigned
    {
        if (is_less(x,y)) return 0;
        auto z = largest_doubling(x,y);
        auto q = 1u;
        x = difference(x,z);
        while (not_equal(z,y)) {
            z = half(z);
            q = twice(q);
            if (not_greater(z,x)) {
                x = difference(x,z);
                q = sum(q,1);
            }
        }
        return q;
    }

    // requires: y > 0
    // returns: (quotient,remainder)
    auto divide_3 (unsigned x, unsigned y) -> std::pair<unsigned,unsigned>
    {
        if (is_less(x,y)) return {0,x};
        auto z = largest_doubling(x,y);
        auto q = 1u;
        x = difference(x,z);
        while (not_equal(z,y)) {
            z = half(z);
            q = twice(q);
            if (not_greater(z,x)) {
                x = difference(x,z);
                q = sum(q,1);
            }
        }
        return {q,x};
    }
}
