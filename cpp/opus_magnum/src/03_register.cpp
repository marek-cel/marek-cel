#include <iostream>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int main()
{
    // "register" to jeszcze jeden typ przydomka (specyfikatora), który może zostać dodany
    // w definicji obiektu. W tym przypadku można ten przydomek zastosować do tzw.
    // zmiennej automatycznej typu całkowitego.

    // >>> ISO C++17 does not allow ‘register’ storage class specifier [-Wregister] <<<

    register int a = 1;

    // Dopisując ten przydomek, dajemy kompilatorowi do zrozumienia, że bardzo zależy
    // nam na szybkim dostępie do tego obiektu (bo np. zaraz będziemy używać takiego
    // obiektu tysiące razy). Kompilator może uwzględnić naszą sugestię i przechowywać ten
    // obiekt w rejestrze, czyli specjalnej komórce, do której ma bardzo szybki, niemal
    // natych mias towy dostęp.

    // Nie ma jednak gwarancji tego, że tak będzie w istocie. Niektóre kompilatory nie są aż
    // tak sprytne. Jak powiedziałem, jest to tylko pobożne życzenie, które kompilator może
    // spełnić lub nie. Większość znanych mi kompilatorów takie sugestie bierze pod uwagę
    // i program wykonuje się nieco szybciej.

    // Jeśli deklarujemy zmienną jako register , to nie możemy starać się uzyskać jej adresu.
    // Rejestr to nie jest kawałek pamięci, więc nie adresuje się go w zwykły sposób. Jeśli
    // więc mimo wszystko spróbujemy dowiadywać się o ten adres, kompilator umieści ten
    // obiekt w zwykłej pamięci, czyli tam, gdzie może nam określić (i podać) jego adres.


    return 0;
}
