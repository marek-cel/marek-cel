public class ConcreteDecoratorB extends Decorator
{
    public ConcreteDecoratorB( Component component )
    {
        super( component );
    }

    public void operation (  )
    {
        super.operation();
        System.out.println( "ConcreteDecoratorB::operation()" );
        addedBehaviour();
    }

    public void addedBehaviour (  )
    {
        System.out.println( "ConcreteDecoratorB::addedBehaviour()" );
    }
}

