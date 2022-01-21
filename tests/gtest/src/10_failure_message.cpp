#include <iostream>

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////

TEST(TestFailureMessage, TestFailureMessage)
{
    EXPECT_TRUE( false ) << "This test failed intentionally!";
}
