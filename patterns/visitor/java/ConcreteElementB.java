public class ConcreteElementB implements Element
{
    @Override
    public void accept ( Visitor v )
    {
        v.visitConcreteElementB( this );
    }

    public void operationB (  )
    {
        System.out.println( "ConcreteElementB::operationB()" );
    }
}

