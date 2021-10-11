import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        ConcreteSubject subject = new ConcreteSubject();
        
        Observer oa = new ConcreteObserverA();
        Observer ob = new ConcreteObserverB();
        
        subject.addObserver( oa );
        subject.addObserver( ob );
        
        subject.setState( 666 );
    }
}
