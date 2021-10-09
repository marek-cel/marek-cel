abstract class Creator 
{
    public void operation()
    {
        Product p = factoryMethod();
        p.doSomething();
    }
    
    protected abstract Product factoryMethod();
}
