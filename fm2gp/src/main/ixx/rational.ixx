module;

#include <concepts>
#include <utility>

export module br.dev.pedrolamarao.number.rational;

import br.dev.pedrolamarao.number.gcd;
import br.dev.pedrolamarao.number.integer;

using namespace std;

export namespace br::dev::pedrolamarao::number
{
    template <Integer I>
    struct rational
    {
        I numerator;
        I denominator;

        rational () noexcept = default;

        constexpr
        // requires d > 0
        // requires { gcd(n,d) == 1 }
        rational (I n, I d) noexcept : numerator(n), denominator(d)
        {}

        static constexpr
        // requires d > 0
        auto reduce (I n, I d) noexcept -> rational
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

    template <Integer I>
    constexpr
    auto sum (rational<I> x, rational<I> y) -> rational<I>
    {
        auto n1 = product(x.numerator,y.denominator);
        auto n2 = product(y.numerator,x.denominator);
        auto n = sum(n1,n2);
        auto d = product(x.denominator,y.denominator);
        return rational<I>::reduce(n,d);
    }

    template <Integer I>
    constexpr
    auto difference (rational<I> x, rational<I> y) -> rational<I>
    {
        auto n1 = product(x.numerator,y.denominator);
        auto n2 = product(y.numerator,x.denominator);
        auto n = difference(n1,n2);
        auto d = product(x.denominator,y.denominator);
        return rational<I>::reduce(n,d);
    }

    template <Integer I>
    constexpr
    auto product (rational<I> x, rational<I> y) -> rational<I>
    {
        auto n = product(x.numerator,y.numerator);
        auto d = product(x.denominator,y.denominator);
        return rational<I>::reduce(n,d);
    }

    template <Integer I>
    constexpr
    auto quotient (rational<I> x, rational<I> y) -> rational<I>
    {
        auto n = product(x.numerator,y.denominator);
        auto d = product(x.denominator,y.numerator);
        return rational<I>::reduce(n,d);
    }

    template <Integer I>
    constexpr
    auto half (rational<I> x) -> rational<I>
    {
        return is_even(x.numerator) ?
            rational(half(x.numerator), x.denominator ) :
            rational( x.numerator, twice(x.denominator) );
    }

    template <Integer I>
    constexpr
    auto twice (rational<I> x) -> rational<I>
    {
        return is_even(x.denominator) ?
            rational( x.numerator, half(x.denominator) ) :
            rational( twice(x.numerator), x.denominator );
    }
}
