public class Hello 
    implements Command
{
    @Override
    public void execute()
    {
        System.out.println( "Hello" );
    }
}
