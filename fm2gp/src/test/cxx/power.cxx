#include <gmock/gmock.h>

import br.dev.pedrolamarao.number.power;

namespace br::dev::pedrolamarao::number
{
    template <>
    auto is_odd (uint32_t x) -> bool
    {
        return (x & 1) == 1;
    }

    template <>
    auto is_odd (uint64_t x) -> bool
    {
        return (x & 1) == 1;
    }

    template <>
    auto is_odd (int32_t x) -> bool
    {
        return (x & 1) == 1;
    }

    template <>
    auto is_odd (int64_t x) -> bool
    {
        return (x & 1) == 1;
    }

    template <>
    auto half (uint32_t x) -> uint32_t
    {
        return x >> 1;
    }

    template <>
    auto half (uint64_t x) -> uint64_t
    {
        return x >> 1;
    }

    template <>
    auto half (int32_t x) -> int32_t
    {
        return x >> 1;
    }

    template <>
    auto half (int64_t x) -> int64_t
    {
        return x >> 1;
    }

    struct sum
    {
        auto operator() (uint32_t x, uint32_t y) const noexcept { return x + y; }
        auto operator() (uint64_t x, uint64_t y) const noexcept { return x + y; }
        auto operator() (int32_t x, int32_t y) const noexcept { return x + y; }
        auto operator() (int64_t x, int64_t y) const noexcept { return x + y; }
        auto operator() (float x, float y) const noexcept { return x + y; }
        auto operator() (double x, double y) const noexcept { return x + y; }
    };

    struct sum_inverse
    {
        auto operator() (int32_t x) const noexcept { return -x; }
        auto operator() (int64_t x) const noexcept { return -x; }
        auto operator() (float x) const noexcept { return -x; }
        auto operator() (double x) const noexcept { return -x; }
    };

    template <>
    struct identity_type <sum,uint32_t> { static constexpr uint32_t value = 0; };

    template <>
    struct identity_type <sum,uint64_t> { static constexpr uint64_t value = 0; };

    template <>
    struct identity_type <sum,int32_t> { static constexpr int32_t value = 0; };

    template <>
    struct identity_type <sum,int64_t> { static constexpr int64_t value = 0; };

    template <>
    struct identity_type <sum,float> { static constexpr float value = 0; };

    template <>
    struct identity_type <sum,double> { static constexpr float value = 0; };

    template <>
    struct inverse_type <sum,int32_t> { using type = sum_inverse; };

    template <>
    struct inverse_type <sum,int64_t> { using type = sum_inverse; };

    template <>
    struct inverse_type <sum,float> { using type = sum_inverse; };

    template <>
    struct inverse_type <sum,double> { using type = sum_inverse; };

    struct product
    {
        auto operator() (uint32_t x, uint32_t y) const noexcept { return x * y; }
        auto operator() (uint64_t x, uint64_t y) const noexcept { return x * y; }
        auto operator() (int32_t x, int32_t y) const noexcept { return x * y; }
        auto operator() (int64_t x, int64_t y) const noexcept { return x * y; }
        auto operator() (float x, float y) const noexcept { return x * y; }
        auto operator() (double x, double y) const noexcept { return x * y; }
    };

    struct product_inverse
    {
        auto operator() (float x) const noexcept { return float{1} / x; }
        auto operator() (double x) const noexcept { return double{1} / x; }
    };

    template <>
    struct identity_type <product,uint32_t> { static constexpr uint32_t value = 1; };

    template <>
    struct identity_type <product,uint64_t> { static constexpr uint64_t value = 1; };

    template <>
    struct identity_type <product,int32_t> { static constexpr int32_t value = 1; };

    template <>
    struct identity_type <product,int64_t> { static constexpr int64_t value = 1; };

    template <>
    struct identity_type <product,float> { static constexpr float value = 1; };

    template <>
    struct identity_type <product,double> { static constexpr double value = 1; };

    template <>
    struct inverse_type <product,float> { using type = product_inverse; };

    template <>
    struct inverse_type <product,double> { using type = product_inverse; };
}

using namespace br::dev::pedrolamarao::number;

TEST(power,sum_unsigned)
{
    ASSERT_EQ( 6, power_monoid(sum(),unsigned{3},2) );
}

TEST(power,sum_signed)
{
    ASSERT_EQ( 6, power_monoid(sum(),signed{3},2) );
}

TEST(power,sum_float)
{
    ASSERT_EQ( 6, power_monoid(sum(),float{3},2) );
}

TEST(power,sum_double)
{
    ASSERT_EQ( 6, power_monoid(sum(),double{3},2) );
}

TEST(power,sum_inverse_signed)
{
    ASSERT_EQ( -6, power_group(sum(),signed{3},-2) );
}

TEST(power,sum_inverse_float)
{
    ASSERT_EQ( -6, power_group(sum(),float{3},-2) );
}

TEST(power,sum_inverse_double)
{
    ASSERT_EQ( -6, power_group(sum(),double{3},-2) );
}

TEST(power,product_unsigned)
{
    ASSERT_EQ( 9, power_monoid(product(),unsigned{3},2) );
}

TEST(power,product_signed)
{
    ASSERT_EQ( 9, power_monoid(product(),signed{3},2) );
}

TEST(power,product_float)
{
    ASSERT_EQ( 9, power_monoid(product(),float{3},2) );
}

TEST(power,product_double)
{
    ASSERT_EQ( 9, power_monoid(product(),float{3},2) );
}

TEST(power,product_inverse_float)
{
    ASSERT_EQ( 0.25, power_group(product(),float{2},-2) );
}

TEST(power,product_inverse_double)
{
    ASSERT_EQ( 0.25, power_group(product(),float{2},-2) );
}
