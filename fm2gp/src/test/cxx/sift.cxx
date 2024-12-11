#include <gmock/gmock.h>

import br.dev.pedrolamarao.fm2gp;

using namespace br::dev::pedrolamarao::fm2gp;

TEST(sift,sift_0)
{
    unsigned sieve [165];
    sift_0(sieve,165);
    ASSERT_TRUE( sieve[0] ); // 3 is prime
    ASSERT_FALSE( sieve[3] ); // 9 is not prime
}

TEST(sift,sift_1)
{
    unsigned sieve [165];
    sift_1(sieve,165);
    ASSERT_TRUE( sieve[0] ); // 3 is prime
    ASSERT_FALSE( sieve[3] ); // 9 is not prime
}

TEST(sift,sift_2)
{
    unsigned sieve [165];
    sift_2(sieve,165);
    ASSERT_TRUE( sieve[0] ); // 3 is prime
    ASSERT_FALSE( sieve[3] ); // 9 is not prime
}

TEST(sift,sift)
{
    constexpr unsigned n = 165;
    unsigned sieve_0 [n];
    unsigned sieve_1 [n];
    unsigned sieve_2 [n];
    sift_0(sieve_0,n);
    sift_1(sieve_1,n);
    sift_2(sieve_2,n);
    for (unsigned i = 0; i < n; i++) {
        ASSERT_EQ( sieve_0[i], sieve_1[i] );
        ASSERT_EQ( sieve_1[i], sieve_2[i] );
    }
}
