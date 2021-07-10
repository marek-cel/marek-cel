#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

struct Box
{
    double a;
    double b;
};

////////////////////////////////////////////////////////////////////////////////

void printBox( const struct Box *box );

void allocateMem();

////////////////////////////////////////////////////////////////////////////////

int main ( int argc, char *argv[] )
{
    printf( "Hello C!\n" );

    struct Box box;

    box.a = 3.14;
    box.b = 2.71;

    printBox( &box );

    allocateMem();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void printBox( const struct Box *box )
{
    printf( "a= %lf\n", box->a );
    printf( "b= %lf\n", box->b );
}

////////////////////////////////////////////////////////////////////////////////

void allocateMem()
{
    size_t size = 8;
    double *buf = (double*)malloc( size * sizeof(double) );

    for ( int i = 0; i < size; i++ )
    {
        buf[ i ] = (double)i / 10.0;
    }

    for ( int i = 0; i < size; i++ )
    {
         printf( "buf= %lf \n", buf[i] );
    }

    free( buf );

}
