public class Client
{
    public void doSomething()
    {
        Subject s = new Proxy();
        s.request();
        s.request();
        s.request();
    }
}

