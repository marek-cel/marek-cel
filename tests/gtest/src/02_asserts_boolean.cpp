#include <iostream>

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////

TEST(GTestAssertBool, AssertTrue)
{
    ASSERT_TRUE(1==1);
    //ASSERT_TRUE(1==2); // Fails
}

////////////////////////////////////////////////////////////////////////////////

TEST(GTestAssertBool, AssertFalse)
{
    //ASSERT_FALSE(1==1); // Fails
    ASSERT_FALSE(1==2);
}
