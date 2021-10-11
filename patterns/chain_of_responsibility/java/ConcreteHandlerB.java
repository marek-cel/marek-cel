public class ConcreteHandlerB extends Handler
{
    public ConcreteHandlerB()
    {
        super();
    }

    public ConcreteHandlerB( Handler successor )
    {
        super( successor );
    }

    @Override
    public void handleRequest (  )
    {
        System.out.println( "ConcreteHandlerB::handleRequest()" );

        if ( checkIfHandled() )
        {
            System.out.println( "ConcreteHandlerB: REQUEST HANDLED" );
        }
        else
        {
            if ( mSuccessor != null )
            {
                mSuccessor.handleRequest();
            }
        }
    }

    private boolean checkIfHandled()
    {
        return false;
    }
}

