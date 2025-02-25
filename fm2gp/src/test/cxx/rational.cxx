#include <gmock/gmock.h>

import br.dev.pedrolamarao.number.integer;
import br.dev.pedrolamarao.number.power;
import br.dev.pedrolamarao.number.rational;

using namespace br::dev::pedrolamarao::number;

namespace
{
    struct sum_
    {
        template <Integer I>
        auto operator() (rational<I> x, rational<I> y) const noexcept { return sum(x,y); }
    };

    struct sum_inverse_
    {
        template <Integer I>
        auto operator() (rational<I> x) const noexcept { return rational(-(x.numerator),x.denominator); }
    };

    struct product_
    {
        template <Integer I>
        auto operator() (rational<I> x, rational<I> y) const noexcept { return product(x,y); }
    };

    struct product_inverse_
    {
        template <Integer I>
        auto operator() (rational<I> x) const noexcept { return rational(x.denominator,x.numerator); }
    };
}

namespace br::dev::pedrolamarao::number
{
    template <Integer I>
    struct identity_type <sum_,rational<I>> { static constexpr rational<I> value = rational(I{0},I{0}); };

    template <Integer I>
    struct inverse_type <sum_,rational<I>> { using type = sum_inverse_; };

    template <Integer I>
    struct identity_type <product_,rational<I>> { static constexpr rational<I> value = rational(I{1},I{1}); };

    template <Integer I>
    struct inverse_type <product_,rational<I>> { using type = product_inverse_; };
}

TEST(rational,reduce)
{
    using rational = rational<int>;
    ASSERT_EQ( rational(2,1), rational::reduce(4,2) );
}

TEST(rational,sum)
{
    using rational = rational<int>;
    ASSERT_EQ( rational(2,1), sum( rational(1,1), rational(1,1) ) );
    ASSERT_EQ( rational(3,2), sum( rational(1,1), rational(1,2) ) );
    ASSERT_EQ( rational(3,1), sum( rational(1,1), rational(2,1) ) );
    ASSERT_EQ( rational(2,1), sum( rational(1,1), rational(2,2) ) );
}

TEST(rational,product)
{
    using rational = rational<int>;
    ASSERT_EQ( rational(1,1), product( rational(1,1), rational(1,1) ) );
    ASSERT_EQ( rational(2,1), product( rational(1,1), rational(2,1) ) );
    ASSERT_EQ( rational(1,2), product( rational(1,1), rational(1,2) ) );
    ASSERT_EQ( rational(1,1), product( rational(1,1), rational(2,2) ) );
}

TEST(rational,twice)
{
    using rational = rational<int>;
    ASSERT_EQ( rational(2,1), twice( rational(1,1) ) );
    ASSERT_EQ( rational(1,1), twice( rational(1,2) ) );
    ASSERT_EQ( rational(4,1), twice( rational(2,1) ) );
    ASSERT_EQ( rational(2,1), twice( rational(2,2) ) );
}

TEST(rational,half)
{
    using rational = rational<int>;
    ASSERT_EQ( rational(1,2), half( rational(1,1) ) );
    ASSERT_EQ( rational(1,4), half( rational(1,2) ) );
    ASSERT_EQ( rational(1,1), half( rational(2,1) ) );
    ASSERT_EQ( rational(1,2), half( rational(2,2) ) );
}

TEST(rational,power_sum)
{
    using rational = rational<unsigned>;
    ASSERT_EQ( rational(6u,1u), power_monoid(sum_(),rational(3u,1u),2) );
}

TEST(rational,power_sum_inverse)
{
    using rational = rational<unsigned>;
    ASSERT_EQ( rational(-6u,1u), power_group(sum_(),rational(3u,1u),-2) );
}

TEST(rational,power_product)
{
    using rational = rational<unsigned>;
    ASSERT_EQ( rational(9u,1u), power_monoid(product_(),rational(3u,1u),2) );
}

TEST(rational,power_product_inverse)
{
    using rational = rational<unsigned>;
    ASSERT_EQ( rational(1u,9u), power_group(product_(),rational(3u,1u),-2) );
}
