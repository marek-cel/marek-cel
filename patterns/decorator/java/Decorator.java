public class Decorator implements Component
{
    private Component mComponent = null;

    public Decorator( Component component )
    {
        mComponent = component;
    }

    public void operation (  )
    {
        System.out.println( "Decorator::operation()" );
        mComponent.operation();
    }
}

