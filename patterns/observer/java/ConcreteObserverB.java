import java.util.*;

public class ConcreteObserverB
    implements Observer
{
    private int mObserverState = 0;

    @Override
    public void update( Observable o, Object arg )
    {
        mObserverState = ((ConcreteSubject)o).getState();
        System.out.println( "ConcreteObserverB::update(Observable,Object) mObserverState= " + String.valueOf(mObserverState) );
    }
}
