import java.util.*;

public class Composite
    implements Component
{
    private List<Component> mComponents = new ArrayList<Component>();
    
    @Override
    public void operation()
    {
        Iterator it = mComponents.iterator();
        
        while( it.hasNext() )
        {
            ( (Component)it.next() ).operation();
        }
    }
    
    public void add( Component component )
    {
        mComponents.add( component );
    }
}
