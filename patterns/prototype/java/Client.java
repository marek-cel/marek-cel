class Client
{
    private ConcretePrototype1 mCp1 = new ConcretePrototype1( 1 );
    private ConcretePrototype2 mCp2 = new ConcretePrototype2( 2 );
    
    public void operation ()
    {
        Prototype p1 = mCp1.clone();
        Prototype p2 = mCp2.clone();

        p1.doSomething();
        p2.doSomething();
    }
}
