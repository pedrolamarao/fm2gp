// Copyright (C) 2024 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

export module br.dev.pedrolamarao.fm2gp;

export namespace br::dev::pedrolamarao::fm2gp
{
    // From Mathematics to Generic Programming

    // Chapter 2: The First Algorithm

    auto is_even (unsigned x) -> bool
    {
        return (x & 1) == 0;
    }

    auto is_odd (unsigned x) -> bool
    {
        return (x & 1) == 1;
    }

    auto half (unsigned x) -> unsigned
    {
        return x >> 1;
    }

    auto twice (unsigned x) -> unsigned
    {
        return x << 1;
    }

    auto multiply_0 (unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return x;
        else return x + multiply_0( x, n - 1 );
    }

    auto multiply_1 (unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return x;
        unsigned r = multiply_1( x + x, half(n) );
        if (is_odd(n)) r = r + x;
        return r;
    }

    auto multiply_accumulate_0 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (n == 1)           return r + x;
        else if (is_odd(n))   return multiply_accumulate_0( r + x, x + x, half(n) );
        else /* is_even(n) */ return multiply_accumulate_0( r, x + x, half(n) );
    }

    auto multiply_accumulate_1 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return r + x;
        if (is_odd(n)) r = r + x;
        return multiply_accumulate_1( r, x + x, half(n) );
    }

    auto multiply_accumulate_2 (unsigned r, unsigned x, unsigned n) -> unsigned
    {
        if (is_odd(n)) {
            r = r + x;
            if (n == 1) return r;
        }
        return multiply_accumulate_2( r, x + x, half(n) );
    }

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

    auto multiply_2 (unsigned x, unsigned n) -> unsigned
    {
        if (n == 1) return x;
        return multiply_accumulate_4(x, x, n - 1);
    }

    auto multiply_3 (unsigned x, unsigned n) -> unsigned
    {
        while (! is_odd(n)) {
            x = x + x;
            n = half(n);
        }
        if (n == 1) return x;
        return multiply_accumulate_4(x, x, n - 1);
    }

    auto multiply_4 (unsigned x, unsigned n) -> unsigned
    {
        while (! is_odd(n)) {
            x = x + x;
            n = half(n);
        }
        if (n == 1) return x;
        return multiply_accumulate_4(x, x + x, half(n - 1));
    }
}
