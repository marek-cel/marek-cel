public class Proxy implements Subject
{
    private RealSubject mRealSubject = null;

    public void request (  )
    {
        create();
        mRealSubject.request();
    }

    private void create()
    {
        if ( mRealSubject == null )
        {
            mRealSubject = new RealSubject();
        }
    }
}

