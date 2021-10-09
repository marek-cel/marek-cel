public class Abstraction
{
    private Implementator mImp = null;

    public Abstraction( Implementator imp )
    {
        mImp = imp;
    }

    public void operation (  )
    {
        mImp.operationImp();
    }
}

