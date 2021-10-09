class ConcretePrototype1 implements Prototype
{
    private int mA = 0;
    
    public ConcretePrototype1( int a )
    {
        mA = a;
    }
    
    public ConcretePrototype1( ConcretePrototype1 cp )
    {
        mA = cp.mA;
    }
    
    @Override
    public Prototype clone ()
    {
        return new ConcretePrototype1( this );
    }

    @Override
    public void doSomething()
    {
        System.out.println( "ConcretePrototype1::doSomething() " + String.valueOf( mA ) );
    }
}
