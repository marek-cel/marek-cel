public class Adapter 
    implements Target
{
    private Adaptee mAdaptee = new Adaptee();
    
    @Override
    public void request()
    {
        mAdaptee.specificRequest();
    }
}
