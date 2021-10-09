public final class Singleton
{
    private static Singleton instance = null;
    
    public static Singleton getInstance()
    {
        if ( instance == null )
        {
            instance = new Singleton();
        }
        
        return instance;
    }
    
    private Singleton() {}
    
    public void doSomething()
    {
        System.out.println( "Singleton::doSomething()" );
    }
}
