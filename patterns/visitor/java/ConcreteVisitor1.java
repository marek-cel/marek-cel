public class ConcreteVisitor1 implements Visitor
{
    @Override
    public void visitConcreteElementA ( ConcreteElementA elementA )
    {
        System.out.println( "ConcreteVisitor1::visitConcreteElementA(ConcreteElementA)" );
        elementA.operationA();
    }

    @Override
    public void visitConcreteElementB ( ConcreteElementB elementB )
    {
        System.out.println( "ConcreteVisitor1::visitConcreteElementB(ConcreteElementB)" );
        elementB.operationB();
    }
}

