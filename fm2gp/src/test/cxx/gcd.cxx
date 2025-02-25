#include <gmock/gmock.h>

import br.dev.pedrolamarao.number.integer;
import br.dev.pedrolamarao.number.gcd;

using namespace br::dev::pedrolamarao::number;

TEST(gcd,gcd_unsigned)
{
    ASSERT_EQ( 1, gcd(unsigned{2},unsigned{3}) );
    ASSERT_EQ( 1, gcd(unsigned{3},unsigned{2}) );

    ASSERT_EQ( 2, gcd(2u,UINT32_MAX-1) );
}
