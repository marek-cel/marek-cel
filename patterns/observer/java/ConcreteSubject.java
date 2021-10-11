import java.util.*;

public class ConcreteSubject extends Observable
{
    private int mState = 0;

    public int getState()
    {
        return mState;
    }

    public void setState( int state )
    {
        mState = state;
        setChanged();
        notifyObservers();
    }
}
