public class Context
{
    private Strategy mStrategy = null;
    
    public void contextInterface()
    {
        mStrategy.algorithmInterface();
    }
    
    public void setStrategy( Strategy strategy )
    {
        mStrategy = strategy;
    }
}
