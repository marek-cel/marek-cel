public class ConcreteHandlerC extends Handler
{
    public ConcreteHandlerC()
    {
        super();
    }

    public ConcreteHandlerC( Handler successor )
    {
        super( successor );
    }

    @Override
    public void handleRequest (  )
    {
        System.out.println( "ConcreteHandlerC::handleRequest()" );

        if ( checkIfHandled() )
        {
            System.out.println( "ConcreteHandlerC: REQUEST HANDLED" );
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
        return true;
    }
}

