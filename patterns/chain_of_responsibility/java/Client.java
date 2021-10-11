public class Client
{
    public void doSomething()
    {
        Handler hc = new ConcreteHandlerC();
        Handler hb = new ConcreteHandlerB( hc );
        Handler ha = new ConcreteHandlerA( hb );

        ha.handleRequest();
    }
}

