package pl.marekcel.dev.cel.patterns.java.command;

import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Command hello = new Hello();
        Command world = new World();
        
        Macro macro = new Macro();
        
        macro.addCommand( hello );
        macro.addCommand( world );
        
        macro.execute();
    }
}
