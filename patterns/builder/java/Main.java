import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Director dir = new Director( new ConcreteBuilder() );
        dir.construct();
    }
}
