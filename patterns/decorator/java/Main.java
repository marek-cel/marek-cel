import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Component cc = new ConcreteComponent();
        Component ca = new ConcreteDecoratorA( cc );
        Component cb = new ConcreteDecoratorB( ca );

        cb.operation();
    }
}
