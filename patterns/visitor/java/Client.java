public class Client
{
    public void doSomething()
    {
        CompositeElement root = new CompositeElement();
        root.add( new ConcreteElementA() );
        root.add( new ConcreteElementB() );

        ConcreteVisitor1 cv1 = new ConcreteVisitor1();
        ConcreteVisitor2 cv2 = new ConcreteVisitor2();

        root.accept( cv1 );
        root.accept( cv2 );
    }
}

