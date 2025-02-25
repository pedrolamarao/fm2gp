module;

#include <concepts>
#include <utility>

export module br.dev.pedrolamarao.number.rational;

import br.dev.pedrolamarao.number.gcd;
import br.dev.pedrolamarao.number.integer;

using namespace std;

export namespace br::dev::pedrolamarao::number
{
    template <Integer Set>
    struct rational
    {
        Set numerator;
        Set denominator;

        rational () noexcept = default;

        template <integral T>
        constexpr
        explicit rational (T t) noexcept : numerator(t), denominator(1)
        {}

        constexpr
        // requires d > 0
        // requires { gcd(n,d) == 1 }
        rational (Set n, Set d) noexcept : numerator{n}, denominator{d}
        {}

        static constexpr
        // requires d > 0
        auto reduce (Set n, Set d) noexcept -> rational
        {
            auto c = gcd(n,d);
            return rational(quotient(n,c),quotient(d,c));
        }

        constexpr
        auto operator== (rational y) const noexcept -> bool
        {
            return numerator == y.numerator &&
                denominator == y.denominator;
        }

        constexpr
        auto operator!= (rational y) const noexcept -> bool
        {
            return numerator != y.numerator ||
                denominator != y.denominator;
        }
    };

    template <Integer Set>
    constexpr
    auto sum (rational<Set> x, rational<Set> y) -> rational<Set>
    {
        auto n1 = product(x.numerator,y.denominator);
        auto n2 = product(y.numerator,x.denominator);
        auto n = sum(n1,n2);
        auto d = product(x.denominator,y.denominator);
        return rational<Set>::reduce(n,d);
    }

    template <Integer Set>
    constexpr
    auto difference (rational<Set> x, rational<Set> y) -> rational<Set>
    {
        auto n1 = product(x.numerator,y.denominator);
        auto n2 = product(y.numerator,x.denominator);
        auto n = difference(n1,n2);
        auto d = product(x.denominator,y.denominator);
        return rational<Set>::reduce(n,d);
    }

    template <Integer Set>
    constexpr
    auto product (rational<Set> x, rational<Set> y) -> rational<Set>
    {
        auto n = product(x.numerator,y.numerator);
        auto d = product(x.denominator,y.denominator);
        return rational<Set>::reduce(n,d);
    }

    template <Integer Set>
    constexpr
    auto quotient (rational<Set> x, rational<Set> y) -> rational<Set>
    {
        auto n = product(x.numerator,y.denominator);
        auto d = product(x.denominator,y.numerator);
        return rational<Set>::reduce(n,d);
    }

    template <Integer Set>
    constexpr
    auto half (rational<Set> x) -> rational<Set>
    {
        return is_even(x.numerator) ?
            rational(half(x.numerator), x.denominator ) :
            rational( x.numerator, twice(x.denominator) );
    }

    template <Integer Set>
    constexpr
    auto twice (rational<Set> x) -> rational<Set>
    {
        return is_even(x.denominator) ?
            rational( x.numerator, half(x.denominator) ) :
            rational( twice(x.numerator), x.denominator );
    }
}
