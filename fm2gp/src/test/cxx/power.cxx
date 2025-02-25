#include <gmock/gmock.h>

import br.dev.pedrolamarao.number.integer;
import br.dev.pedrolamarao.number.power;

namespace
{
    struct sum_
    {
        auto operator() (uint32_t x, uint32_t y) const noexcept { return x + y; }
        auto operator() (uint64_t x, uint64_t y) const noexcept { return x + y; }
        auto operator() (int32_t x, int32_t y) const noexcept { return x + y; }
        auto operator() (int64_t x, int64_t y) const noexcept { return x + y; }
        auto operator() (float x, float y) const noexcept { return x + y; }
        auto operator() (double x, double y) const noexcept { return x + y; }
    };

    struct sum_inverse_
    {
        auto operator() (int32_t x) const noexcept { return -x; }
        auto operator() (int64_t x) const noexcept { return -x; }
        auto operator() (float x) const noexcept { return -x; }
        auto operator() (double x) const noexcept { return -x; }
    };

    struct product_
    {
        auto operator() (uint32_t x, uint32_t y) const noexcept { return x * y; }
        auto operator() (uint64_t x, uint64_t y) const noexcept { return x * y; }
        auto operator() (int32_t x, int32_t y) const noexcept { return x * y; }
        auto operator() (int64_t x, int64_t y) const noexcept { return x * y; }
        auto operator() (float x, float y) const noexcept { return x * y; }
        auto operator() (double x, double y) const noexcept { return x * y; }
    };

    struct product_inverse_
    {
        auto operator() (float x) const noexcept { return float{1} / x; }
        auto operator() (double x) const noexcept { return double{1} / x; }
    };
}

namespace br::dev::pedrolamarao::number
{
    template <>
    struct identity_type <sum_,uint32_t> { static constexpr uint32_t value = 0; };

    template <>
    struct identity_type <sum_,uint64_t> { static constexpr uint64_t value = 0; };

    template <>
    struct identity_type <sum_,int32_t> { static constexpr int32_t value = 0; };

    template <>
    struct identity_type <sum_,int64_t> { static constexpr int64_t value = 0; };

    template <>
    struct identity_type <sum_,float> { static constexpr float value = 0; };

    template <>
    struct identity_type <sum_,double> { static constexpr float value = 0; };

    template <>
    struct inverse_type <sum_,int32_t> { using type = sum_inverse_; };

    template <>
    struct inverse_type <sum_,int64_t> { using type = sum_inverse_; };

    template <>
    struct inverse_type <sum_,float> { using type = sum_inverse_; };

    template <>
    struct inverse_type <sum_,double> { using type = sum_inverse_; };

    template <>
    struct identity_type <product_,uint32_t> { static constexpr uint32_t value = 1; };

    template <>
    struct identity_type <product_,uint64_t> { static constexpr uint64_t value = 1; };

    template <>
    struct identity_type <product_,int32_t> { static constexpr int32_t value = 1; };

    template <>
    struct identity_type <product_,int64_t> { static constexpr int64_t value = 1; };

    template <>
    struct identity_type <product_,float> { static constexpr float value = 1; };

    template <>
    struct identity_type <product_,double> { static constexpr double value = 1; };

    template <>
    struct inverse_type <product_,float> { using type = product_inverse_; };

    template <>
    struct inverse_type <product_,double> { using type = product_inverse_; };
}

using namespace br::dev::pedrolamarao::number;

TEST(power,sum_unsigned)
{
    ASSERT_EQ( 6, power_monoid(sum_(),unsigned{3},2) );
}

TEST(power,sum_signed)
{
    ASSERT_EQ( 6, power_monoid(sum_(),signed{3},2) );
}

TEST(power,sum_float)
{
    ASSERT_EQ( 6, power_monoid(sum_(),float{3},2) );
}

TEST(power,sum_double)
{
    ASSERT_EQ( 6, power_monoid(sum_(),double{3},2) );
}

TEST(power,sum_inverse_signed)
{
    ASSERT_EQ( -6, power_group(sum_(),signed{3},-2) );
}

TEST(power,sum_inverse_float)
{
    ASSERT_EQ( -6, power_group(sum_(),float{3},-2) );
}

TEST(power,sum_inverse_double)
{
    ASSERT_EQ( -6, power_group(sum_(),double{3},-2) );
}

TEST(power,product_unsigned)
{
    ASSERT_EQ( 9, power_monoid(product_(),unsigned{3},2) );
}

TEST(power,product_signed)
{
    ASSERT_EQ( 9, power_monoid(product_(),signed{3},2) );
}

TEST(power,product_float)
{
    ASSERT_EQ( 9, power_monoid(product_(),float{3},2) );
}

TEST(power,product_double)
{
    ASSERT_EQ( 9, power_monoid(product_(),float{3},2) );
}

TEST(power,product_inverse_float)
{
    ASSERT_EQ( 0.25, power_group(product_(),float{2},-2) );
}

TEST(power,product_inverse_double)
{
    ASSERT_EQ( 0.25, power_group(product_(),float{2},-2) );
}
