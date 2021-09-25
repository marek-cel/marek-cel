package pl.marekcel.dev.cel.patterns.java.composite;

public class Leaf
    implements Component
{
    private String mName = "";
    
    public Leaf( String name )
    {
        mName = name;
    }

    @Override
    public void doSomething()
    {
        System.out.println( "My name is " + mName );
    }
}
