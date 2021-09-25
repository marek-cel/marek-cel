package pl.marekcel.dev.cel.patterns.java.observer;

import java.util.*;

public class ConcreteSubject extends Observable
{
    public void event()
    {
        setChanged();
        notifyObservers();
    }
}
