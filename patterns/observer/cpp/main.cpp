#include <memory>

#include "ConcreteObserverA.h"
#include "ConcreteObserverB.h"

#include "ConcreteSubject.h"

int main( int argc, char *argv[] )
{
    std::shared_ptr<ConcreteSubject> subject = std::make_shared<ConcreteSubject>();

    std::shared_ptr<Observer> oa = std::make_shared<ConcreteObserverA>( subject );
    std::shared_ptr<Observer> ob = std::make_shared<ConcreteObserverB>( subject );

    subject->attach( oa );
    subject->attach( ob );

    subject->setState( 666 );

    return 0;
}
