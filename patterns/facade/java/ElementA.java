package pl.marekcel.dev.cel.patterns.java.facade;

class ElementA
{
    private int mX;
    
    public ElementA( int x )
    {
        mX = x;
    }
    
    public void doSomething()
    {
        System.out.println( "ElementA " + String.valueOf(mX) );
    }
}
