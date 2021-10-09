public class Leaf
    implements Component
{
    private String mName = "";
    
    public Leaf( String name )
    {
        mName = name;
    }

    @Override
    public void operation()
    {
        System.out.println( "Leaf::operation() name= " + mName );
    }
}
