package pl.marekcel.dev.cel.patterns.java.strategy;

public class Context
{
    private Strategy mStrategy = null;
    
    private int mData[] = { 1, 2, 3, 4 };
    
    public void doSomething()
    {
        mStrategy.execute( mData );
    }
    
    public void setStrategy( Strategy strategy )
    {
        mStrategy = strategy;
    }
}
