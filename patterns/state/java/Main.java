import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Context c = new Context();

        c.request();
        c.setStateB();
        c.request();
    }
}
