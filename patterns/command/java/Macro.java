package pl.marekcel.dev.cel.patterns.java.command;

import java.util.*;

public class Macro
    implements Command
{
    private List<Command> mCommands = new ArrayList<Command>();
    
    @Override
    public void execute()
    {
        Iterator it = mCommands.iterator();
        
        while( it.hasNext() )
        {
            ( (Command)it.next() ).execute();
        }
    }
    
    public void addCommand( Command command )
    {
        mCommands.add( command );
    }
}
