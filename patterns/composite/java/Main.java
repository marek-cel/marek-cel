package pl.marekcel.dev.cel.patterns.java.composite;

import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Composite root = new Composite();
        Composite group = new Composite();
        
        Leaf a = new Leaf( "A" );
        Leaf b = new Leaf( "B" );
        Leaf c = new Leaf( "C" );
        
        root.add( a );
        root.add( group );
        
        group.add( b );
        group.add( c );
        
        root.doSomething();
    }
}
