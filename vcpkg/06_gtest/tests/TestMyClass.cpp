#include <gtest/gtest.h>

#include <MyClass.h>

class TestMyClass : public ::testing::Test
{
protected:

    TestMyClass() {}
    virtual ~TestMyClass() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMyClass, CanGetOne)
{
    MyClass a;
    EXPECT_EQ(a.getOne(), 1);
}

TEST_F(TestMyClass, CanGetTwo)
{
    MyClass a;
    EXPECT_EQ(a.getTwo(), 2);
}
