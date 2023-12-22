#include <iostream>
#include <memory>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

template <class... T>
auto add(T... args)
{
    return (... + args);
}

////////////////////////////////////////////////////////////////////////////////

template <class T, class... Args>
auto make_unique(Args... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

////////////////////////////////////////////////////////////////////////////////

// Base case for recursion
template <typename T>
void pack(std::vector<vector<T>*>& vec) {}

template <typename T, typename... Args>
void pack(vector<vector<T>*>& vec, vector<T>* first, Args... args)
{
    first->push_back(3.14);
    vec.push_back(first);
    pack(vec, args...);
}

template <typename T, typename... Args>
void read(const char* str, vector<T>* first, Args... args)
{
    vector<vector<T>*> vec;
    pack(vec, first, args...);
    cout << str << endl;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << __cplusplus << endl << endl;

    //cout << add(1.1, 2.2, 3.14) << endl;

    vector<double> x1;
    vector<double> x2;

    read("test", &x1, &x2);

    for ( auto x : x1 )
    {
        cout << x << endl;
    }

    return 0;
}
