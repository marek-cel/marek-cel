public class Originator
{
    private int mState = 0;

    public void setMemento ( Memento m )
    {
        mState = m.getState();
    }

    public Memento createMemento (  )
    {
        Memento m = new Memento();
        m.setState( mState );
        return m;
    }

    public void operation()  { mState = 1; }

    public void printState()
    {
        System.out.println( "Originator::printState() state= " + String.valueOf( mState ) );
    }

    public static class Memento
    {
        private int mState = 0;

        private int getState()
        {
            return mState;
        }

        private void setState( int state )
        {
            mState = state;
        }
    }
}

