package pl.marekcel.dev.cel.patterns.java.singleton;

public final class Singleton
{
    private static Singleton instance = new Singleton();
    
    public static Singleton getInstance()
    {
        return instance;
    }
    
    private Singleton() {}
    
    public void doSomething()
    {
        System.out.println( "Singleton::doSomething()" );
    }
}
