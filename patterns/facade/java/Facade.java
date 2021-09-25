package pl.marekcel.dev.cel.patterns.java.facade;

public class Facade
{
    private ElementA mElementA = new ElementA( 1 );
    private ElementB mElementB = new ElementB( 2 );
    private ElementC mElementC = new ElementC( 3 );

    public void doSomething()
    {
        mElementA.doSomething();
        mElementB.doSomething();
        mElementC.doSomething();
    }
}
