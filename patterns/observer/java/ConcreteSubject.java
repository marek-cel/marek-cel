import java.util.*;

public class ConcreteSubject extends Observable
{
    public void event()
    {
        setChanged();
        notifyObservers();
    }
}
