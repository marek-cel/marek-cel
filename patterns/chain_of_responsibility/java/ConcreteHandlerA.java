public class ConcreteHandlerA extends Handler
{
    public ConcreteHandlerA()
    {
        super();
    }

    public ConcreteHandlerA( Handler successor )
    {
        super( successor );
    }

    @Override
    public void handleRequest (  )
    {
        System.out.println( "ConcreteHandlerA::handleRequest()" );

        if ( checkIfHandled() )
        {
            System.out.println( "ConcreteHandlerA: REQUEST HANDLED" );
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

