public class ConcreteVisitor2 implements Visitor
{
    @Override
    public void visitConcreteElementA ( ConcreteElementA elementA )
    {
        System.out.println( "ConcreteVisitor2::visitConcreteElementA(ConcreteElementA)" );
        elementA.operationA();
    }

    @Override
    public void visitConcreteElementB ( ConcreteElementB elementB )
    {
        System.out.println( "ConcreteVisitor2::visitConcreteElementB(ConcreteElementB)" );
        elementB.operationB();
    }
}

