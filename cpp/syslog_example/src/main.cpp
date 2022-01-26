#include <syslog.h>
#include <unistd.h>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello World!" << endl;
#   ifdef _LINUX_
    cout << "_LINUX_" << endl;
#   endif

    int i = 0;

    for (;;)
    {
        cout << "tik= " << i << endl;
        syslog( LOG_INFO, "Message format string tik= %d", i );

        ++i;

        usleep( 1e6 );
    }

    return 0;
}
