class ElementC
{
    private double mX;
    
    public ElementC( double x )
    {
        mX = x;
    }
    
    public void doSomething()
    {
        System.out.println( "ElementC " + String.valueOf(mX) );
    }
}
