#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    int zmienna = 5;
    int *inny_wsk = &zmienna;

    auto *wsk1 = &zmienna;
    auto *wsk2 = inny_wsk;

    auto wsk3 = &zmienna;
    auto wsk4 = inny_wsk;

    cout << "zmienna= " << zmienna << endl;

    cout << "inny_wsk= " << (*inny_wsk) << endl;

    cout << "wsk1= " << (*wsk1) << endl;
    cout << "wsk2= " << (*wsk2) << endl;
    cout << "wsk3= " << (*wsk3) << endl;
    cout << "wsk4= " << (*wsk4) << endl;

    return 0;
}
