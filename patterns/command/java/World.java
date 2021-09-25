package pl.marekcel.dev.cel.patterns.java.command;

public class World 
    implements Command
{
    @Override
    public void execute()
    {
        System.out.println( "World" );
    }
}
