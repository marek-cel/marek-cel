public class ConcreteMediator implements Mediator
{
    private ConcreteColleagueB mColleagueB = null;
    private ConcreteColleagueA mColleagueA = null;

    public ConcreteMediator()
    {
        mColleagueA = new ConcreteColleagueA( this );
        mColleagueB = new ConcreteColleagueB( this );
    }

    public void invokeEventA() { mColleagueA.handleEvent(); }
    public void invokeEventB() { mColleagueB.handleEvent(); }

    @Override
    public void colleagueChanged( Colleague colleague )
    {
        if ( colleague == mColleagueA )
        {
            System.out.println( "ConcreteMediator::colleagueChanged(Colleague*) colleagueA changed" );
            mColleagueB.doSomething();
        }
        else if ( colleague == mColleagueB )
        {
            System.out.println( "ConcreteMediator::colleagueChanged(Colleague*) colleagueB changed" );
            mColleagueA.doSomething();
        }
    }
}

