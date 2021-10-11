import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Context context = new Context();
        
        Strategy sa = new ConcreteStrategyA();
        Strategy sb = new ConcreteStrategyB();
        Strategy sc = new ConcreteStrategyC();
        
        context.setStrategy( sa );
        context.contextInterface();

        context.setStrategy( sb );
        context.contextInterface();

        context.setStrategy( sc );
        context.contextInterface();
    }
}
