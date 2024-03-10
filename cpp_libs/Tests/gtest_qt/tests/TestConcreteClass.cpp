#include <gtest/gtest.h>

#include <ConcreteClass.h>

////////////////////////////////////////////////////////////////////////////////

TEST(TestConcreteClass, CanInstantiate)
{
    EXPECT_NO_THROW( ConcreteClass concreteClass );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestConcreteClass, CanConstruct)
{
    ConcreteClass *concreteClass = nullptr;
    EXPECT_NO_THROW( concreteClass = new ConcreteClass );
    delete concreteClass;
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestConcreteClass, CanDestruct)
{
    ConcreteClass *concreteClass = nullptr;
    concreteClass = new ConcreteClass;
    EXPECT_NO_THROW( delete concreteClass );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestConcreteClass, CanDestructParent)
{
    AbstractClass *abstractClass = nullptr;
    abstractClass = new ConcreteClass;
    EXPECT_NO_THROW( delete abstractClass );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestConcreteClass, CanGetOne)
{
    ConcreteClass concreteClass;
    EXPECT_EQ( 1, concreteClass.getOne() );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestConcreteClass, CanGetTwo)
{
    ConcreteClass concreteClass;
    EXPECT_EQ( 2, concreteClass.getTwo() );
}
