public class Client
{
    public void action()
    {
        Target t = new Adapter();
        t.request();
    }
}
