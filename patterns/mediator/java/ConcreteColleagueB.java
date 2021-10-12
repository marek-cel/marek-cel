public class ConcreteColleagueB extends Colleague
{
    public ConcreteColleagueB( Mediator mediator )
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

