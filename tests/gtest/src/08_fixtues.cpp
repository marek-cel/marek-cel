#include <iostream>

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////

class TestFixtureName : public ::testing::Test
{
protected:

    void SetUp() override
    {
        // do something
    }

    void TearDown() override
    {
        // do something
    }

    int _var1 { 1 };
    int _var2 { 2 };
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFixtureName, IsVar1Equals1)
{
    ASSERT_EQ( _var1, 1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestFixtureName, IsVar2Equals2)
{
    ASSERT_EQ( _var2, 2 );
}
