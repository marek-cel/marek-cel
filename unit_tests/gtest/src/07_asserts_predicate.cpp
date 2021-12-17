#include <iostream>

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////

bool isInRange( int x, int min, int max )
{
    return x > min ? x < max ? true : false : false;
}

////////////////////////////////////////////////////////////////////////////////

TEST(GTestAssertPredicate, AssertPredicate)
{
    ASSERT_PRED3( isInRange, 3, 2, 5 );
    //ASSERT_PRED3( isInRange, 1, 2, 5 ); // Fails
}
