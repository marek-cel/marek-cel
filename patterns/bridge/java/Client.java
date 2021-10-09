public class Client
{
    public void doSomething()
    {
        Implementator impA = new ConcreteImplementatorA();
        Implementator impB = new ConcreteImplementatorB();

        Abstraction a = new RefinedAbstraction( impA );

        a.operation();
    }
}

