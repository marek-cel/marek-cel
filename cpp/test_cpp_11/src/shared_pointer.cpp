#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class MyClass
{
public:

    MyClass()
    {
        cout << "MyClass()" << endl;
    }

    ~MyClass()
    {
        cout << "~MyClass()" << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////

class Storage
{
public:

    Storage()
    {
        _mc1 = std::make_shared< MyClass >();
        _mc2 = std::make_shared< MyClass >();
    }

    std::shared_ptr< MyClass > getMC1() { return _mc1; }

private:

    std::shared_ptr< MyClass > _mc1;
    std::shared_ptr< MyClass > _mc2;
};

////////////////////////////////////////////////////////////////////////////////

int main()
{
    Storage *s = new Storage();

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;

    std::shared_ptr< MyClass > mc1 = s->getMC1();

    delete s;

    cout << __FILE__ << "(" << __LINE__ << ")" << endl;

    return 0;
}
