#include <iostream>
#include <memory>

#include <boost/signals2.hpp>

struct HelloWorld
{
    void operator()(int num) const
    {
        std::cout << num << " Hello, world! (functor)" << std::endl;
    }
};

void foo(int num)
{
    std::cout << num << " Hello, world! (function)" << std::endl;
}

class MyClass
{
public:

    MyClass(int num)
    {
        _num = num;
    }

    void exec()
    {
        _sig.connect(boost::bind(&MyClass::onSignal, this, boost::placeholders::_1));
        _sig(20);
    }

    void onSignal(int num)
    {
        std::cout << _num << " " << num << " MyClass::onSignal(int)" << std::endl;
    }

private:

    int _num = -1;

    boost::signals2::signal<void(int)> _sig;

};

int main()
{
    boost::signals2::signal<void(int)> sig;

    // ordered call of slots
    std::cout << std::endl;
    HelloWorld hello;
    boost::signals2::connection cFunctor  = sig.connect(1, hello);
    boost::signals2::connection cFunction = sig.connect(2, &foo);
    boost::signals2::connection cLambda   = sig.connect(0, [](int num)
    {
        std::cout << num << " Hello, world! (lambda)" << std::endl;
    });
    sig(2);

    // checking connection
    std::cout << std::endl;
    if ( cFunctor.connected() )
    {
        std::cout << "Functor is connected" << std::endl;
    }

    // disconnecting
    cFunctor.disconnect();
    // disconnecting already disconnected slot (safe)
    cFunctor.disconnect();
    sig(3);

    // temporarily blocking slot
    std::cout << std::endl;
    {
        boost::signals2::shared_connection_block block(cFunction);
        sig(4);
    }
    sig(5);

    // disconnect "by slot"
    std::cout << std::endl;
    sig.disconnect(&foo);
    sig(6);

    //
    std::cout << std::endl;
    MyClass myClass(1);
    boost::signals2::signal<void(int)> sigMyClass;
    sigMyClass.connect(boost::bind(&MyClass::onSignal, &myClass, boost::placeholders::_1));
    sigMyClass(10);
    myClass.exec();

    // automatic connection management
    std::cout << std::endl;
    {
        boost::shared_ptr<MyClass> myClass2(new MyClass(2));
        sigMyClass.connect(
            boost::signals2::signal<void(int)>::slot_type(
                &MyClass::onSignal, myClass2.get(), boost::placeholders::_1
            ).track(myClass2)
        );
        sigMyClass(30);
    }
    sigMyClass(40);

    // signal delayed execution
    std::cout << std::endl;
    sig(7);

    // disconnecting all slots
    std::cout << std::endl;
    std::cout << "Disconnecting all slots" << std::endl;
    sig.disconnect_all_slots();
    sigMyClass.disconnect_all_slots();
    sig(8);
    sigMyClass(50);

    return 0;
}