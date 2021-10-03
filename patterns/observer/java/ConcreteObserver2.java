import java.util.*;

public class ConcreteObserver2
    implements Observer
{
    @Override
    public void update( Observable o, Object arg )
    {
        System.out.println( "Observer2" );
    }
}
