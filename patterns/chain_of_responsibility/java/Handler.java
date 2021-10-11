public abstract class Handler
{
    protected Handler mSuccessor = null;

    abstract public void handleRequest (  );

    public Handler() {}

    public Handler( Handler successor )
    {
        mSuccessor = successor;
    }
}

