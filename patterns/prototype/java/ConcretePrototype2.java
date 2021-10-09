class ConcretePrototype2 implements Prototype
{
    private int mA = 0;
    
    public ConcretePrototype2( int a )
    {
        mA = a;
    }
    
    public ConcretePrototype2( ConcretePrototype2 cp )
    {
        mA = cp.mA;
    }
    
    @Override
    public Prototype clone ()
    {
        return new ConcretePrototype2( this );
    }

    @Override
    public void doSomething()
    {
        System.out.println( "ConcretePrototype2::doSomething() " + String.valueOf( mA ) );
    }
}
