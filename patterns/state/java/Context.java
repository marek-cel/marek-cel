public class Context
{
    private State mState = new ConcreteStateA();

    public void request (  )
    {
        mState.handle();
    }

    public void setStateA()
    {
        mState = new ConcreteStateA();
    }

    public void setStateB()
    {
        mState = new ConcreteStateB();
    }
}

