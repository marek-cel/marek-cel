#include "Context.h"

int main( int argc, char *argv[] )
{
    Context c;

    c.request();
    c.setStateB();
    c.request();

    return 0;
}
