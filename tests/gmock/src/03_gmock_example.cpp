#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

////////////////////////////////////////////////////////////////////////////////

class IQueue
{
public:

    virtual ~IQueue() {}

    virtual void enqueue( int data ) = 0;
    virtual int dequeue() = 0;
};

////////////////////////////////////////////////////////////////////////////////

class MockQueue : public IQueue
{
public:

    MOCK_METHOD0( dequeue, int() );
    MOCK_METHOD1( enqueue, void(int data) );
};

////////////////////////////////////////////////////////////////////////////////

class DataHolder
{
public:

    DataHolder( IQueue *queue ) : _queue( queue ) {}

    void addData( int var )
    {
        _queue->enqueue( var );
    }

    int getData()
    {
        return _queue->dequeue();
    }

private:

    IQueue *_queue;
};

////////////////////////////////////////////////////////////////////////////////

TEST(GMock_Example, CanAddData)
{
    MockQueue mq;
    DataHolder dh( &mq );

    EXPECT_CALL( mq, enqueue(_) );

    dh.addData( 1 );
}

////////////////////////////////////////////////////////////////////////////////

TEST(GMock_Example, CanAddAndGetData)
{
    MockQueue mq;
    DataHolder dh( &mq );

    EXPECT_CALL( mq, enqueue(1) );
    EXPECT_CALL( mq, dequeue() ).WillOnce( Return(1) );

    dh.addData( 1 );
    int data = dh.getData();

    ASSERT_EQ( data, 1 );
}
