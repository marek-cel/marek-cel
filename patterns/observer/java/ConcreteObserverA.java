import java.util.*;

public class ConcreteObserverA
    implements Observer
{
    private int mObserverState = 0;

    @Override
    public void update( Observable o, Object arg )
    {
        mObserverState = ((ConcreteSubject)o).getState();
        System.out.println( "ConcreteObserverA::update(Observable,Object) mObserverState= " + String.valueOf(mObserverState) );
    }
}
