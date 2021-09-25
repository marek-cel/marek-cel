#include <memory>

#include "ConcreteObserver1.h"
#include "ConcreteObserver2.h"
#include "ConcreteSubject.h"

int main( int argc, char *argv[] )
{
    std::shared_ptr<ConcreteSubject> subject = std::make_shared<ConcreteSubject>();

    std::shared_ptr<ConcreteObserver1> observer1 = std::make_shared<ConcreteObserver1>();
    std::shared_ptr<ConcreteObserver2> observer2 = std::make_shared<ConcreteObserver2>();

    subject->addObserver( observer1 );
    subject->addObserver( observer2 );

    subject->event();

    return 0;
}
