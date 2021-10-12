public class ConcreteColleagueA extends Colleague
{
    public ConcreteColleagueA( Mediator mediator )
    {
        super( mediator );
    }

    public void handleEvent()
    {
        System.out.println( "ConcreteColleagueA::handleEvent()" );
        changed();
    }

    public void doSomething()
    {
        System.out.println( "ConcreteColleagueA::doSomething()" );
    }
}

