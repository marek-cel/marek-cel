#include <gtest/gtest.h>

#include <InterfaceImplementation.h>

////////////////////////////////////////////////////////////////////////////////

TEST(TestInterfaceImplementation, CanInstantiate)
{
    EXPECT_NO_THROW( InterfaceImplementation interfaceImplementation );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestInterfaceImplementation, CanConstruct)
{
    InterfaceImplementation *interfaceImplementation = nullptr;
    EXPECT_NO_THROW( interfaceImplementation = new InterfaceImplementation );
    delete interfaceImplementation;
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestInterfaceImplementation, CanDestruct)
{
    InterfaceImplementation *interfaceImplementation = nullptr;
    interfaceImplementation = new InterfaceImplementation;
    EXPECT_NO_THROW( delete interfaceImplementation );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestInterfaceImplementation, CanDestructParent)
{
    Interface *interface = nullptr;
    interface = new InterfaceImplementation;
    EXPECT_NO_THROW( delete interface );
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestInterfaceImplementation, CanGetOne)
{
    InterfaceImplementation interfaceImplementation;
    EXPECT_EQ( 1, interfaceImplementation.getOne() );
}
