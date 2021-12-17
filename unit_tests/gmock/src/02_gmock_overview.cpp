#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Ge;
using ::testing::NotNull;
using ::testing::Return;

////////////////////////////////////////////////////////////////////////////////

class Obj
{
public:
    Obj() {}
};

////////////////////////////////////////////////////////////////////////////////

class IObj
{
public:

    virtual ~IObj() {}

    virtual void funInt( int data ) = 0;
    virtual void funObj( Obj *obj ) = 0;
};

////////////////////////////////////////////////////////////////////////////////

class MockObj : public IObj
{
public:

    MOCK_METHOD( void, funInt, (int data) );
    MOCK_METHOD( void, funObj, (Obj *obj) );
};

////////////////////////////////////////////////////////////////////////////////

class Client
{
public:

    Client( IObj *obj ) : _obj( obj ) {}

    void funInt( int var )
    {
        _obj->funInt( var );
    }

    void funInt2( int var )
    {
        _obj->funInt( var );
        _obj->funInt( var );
    }

    void funObj( Obj *obj )
    {
        _obj->funObj( obj );
    }

private:

    IObj *_obj;
};

////////////////////////////////////////////////////////////////////////////////

TEST(GMock_Overview, Matchers)
{
    // Matchers
    MockObj mockObj;
    Client clien( &mockObj );

    Obj obj;

    EXPECT_CALL( mockObj, funInt(_) );              // any value
    EXPECT_CALL( mockObj, funInt( Ge( 100 ) ) );    // greater or equal 100
    EXPECT_CALL( mockObj, funObj( NotNull() ) );    // not null object

    clien.funInt( 1 );
    clien.funInt( 101 );
    clien.funObj( &obj );
}

////////////////////////////////////////////////////////////////////////////////

TEST(GMock_Overview, TimesClauses)
{
    // Times Clauses
    MockObj mockObj;
    Client clien( &mockObj );

    Obj obj;

    EXPECT_CALL( mockObj, funInt(_) ).Times(2);
    EXPECT_CALL( mockObj, funObj( NotNull() ) ).WillOnce( Return() );

    clien.funInt2( 1 );
    clien.funObj( &obj );
}
