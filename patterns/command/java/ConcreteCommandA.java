public class ConcreteCommandA
    implements Command
{
    private ReceiverA mRecv = null;

    public ConcreteCommandA( ReceiverA recv )
    {
        mRecv = recv;
    }

    @Override
    public void execute()
    {
        System.out.println( "ConcreteCommandA::execute()" );
        mRecv.actionA();
    }
}
