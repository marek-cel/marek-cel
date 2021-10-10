public class Client
{
    public void doSomething()
    {
        ReceiverA ra = new ReceiverA();
        ReceiverB rb = new ReceiverB();

        Command ca = new ConcreteCommandA( ra );
        Command cb = new ConcreteCommandB( rb );

        MacroCommand macro = new MacroCommand();

        macro.addCommand( ca );
        macro.addCommand( cb );

        macro.execute();
    }
}