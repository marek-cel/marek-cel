public class ConcreteDecoratorA extends Decorator
{
    public  int mAddedState = 0;

    public ConcreteDecoratorA( Component component )
    {
        super( component );
    }

    public void operation (  )
    {
        super.operation();
        System.out.println( "ConcreteDecoratorA::operation()" );
    }
}

