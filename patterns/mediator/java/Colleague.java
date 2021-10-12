public class Colleague
{
    protected Mediator mMediator = null;

    public Colleague( Mediator mediator )
    {
        mMediator = mediator;
    }

    protected void changed()
    {
        mMediator.colleagueChanged( this );
    }
}

