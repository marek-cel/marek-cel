class ElementB
{
    private long mX;
    
    public ElementB( long x )
    {
        mX = x;
    }
    
    public void doSomething()
    {
        System.out.println( "ElementB " + String.valueOf(mX) );
    }
}
