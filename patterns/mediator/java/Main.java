import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        ConcreteMediator cm = new ConcreteMediator();
        cm.invokeEventA();
        cm.invokeEventB();
    }
}
