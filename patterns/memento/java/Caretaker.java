public class Caretaker
{
    private Originator.Memento mMemento = null;

    public void doSomething()
    {
        Originator o = new Originator();
        o.printState();

        Originator.Memento m = o.createMemento();

        o.operation();
        o.printState();

        o.setMemento( m );
        o.printState();
    }
}

