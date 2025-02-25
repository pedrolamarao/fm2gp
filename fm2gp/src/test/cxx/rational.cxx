#include <gmock/gmock.h>

import br.dev.pedrolamarao.number.rational;

using namespace br::dev::pedrolamarao::number;

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
