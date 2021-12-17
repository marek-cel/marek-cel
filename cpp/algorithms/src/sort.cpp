#include <algorithm>
#include <execution>
#include <iostream>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void init( std::vector<int> &v )
{
    for ( int i = 0; i < 5; i++ )
    {
        v.push_back( rand() % 10 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void print( std::vector<int> &v )
{
    for ( auto a : v )
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void bubble_sort( std::vector<int> &v )
{
    for ( size_t i = 0; i < v.size(); i++ )
    {
        for ( size_t j = i; j > 0; j-- )
        {
            if ( v[j] < v[j-1] )
            {
                //int temp = v[j];
                //v[j] = v[j-1];
                //v[j-1] = temp;

                std::swap( v[j], v[j-1] );
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    srand( time(NULL) );

    std::vector<int> v;

    init( v );
    print( v );

    std::cout << std::endl;

    std::vector<int> v1 = v;
    std::vector<int> v2 = v;
    std::vector<int> v3 = v;

    bubble_sort( v1 );
    std::sort( v2.begin(), v2.end(), std::less<int>() );
    std::sort( std::execution::par, v3.begin(), v3.end() ); // C++17

    print( v1 );
    print( v2 );
    print( v3 );

    return 0;
}
