public class ConcreteCommandB
    implements Command
{
    private ReceiverB mRecv = null;

    public ConcreteCommandB( ReceiverB recv )
    {
        mRecv = recv;
    }

    @Override
    public void execute()
    {
        System.out.println( "ConcreteCommandB::execute()" );
        mRecv.actionB();
    }
}
