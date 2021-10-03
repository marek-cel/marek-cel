import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        ConcreteSubject subject = new ConcreteSubject();
        
        ConcreteObserver1 observer1 = new ConcreteObserver1();
        ConcreteObserver2 observer2 = new ConcreteObserver2();
        
        subject.addObserver( observer1 );
        subject.addObserver( observer2 );
        
        subject.event();
    }
}
