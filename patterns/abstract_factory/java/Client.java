public class Client
{
    private AbstractFactory mAf = null;
    
    private AbstractProductA mProductA = null;
    private AbstractProductB mProductB = null;

    public Client( AbstractFactory af )
    {
        mAf = af;
        
        mProductA = mAf.createProductA();
        mProductB = mAf.createProductB();
    }
    
    public void doSomething()
    {
        mProductA.doSomething();
        mProductB.doSomething();
    }
}
