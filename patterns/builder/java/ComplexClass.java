public class ComplexClass
{
    private ComponentA mComponentA = null;
    private ComponentB mComponentB = null;

    public ComplexClass() {}

    public void addComponentA( ComponentA componentA )
    {
        mComponentA = componentA;
    }

    public void addComponentB( ComponentB componentB )
    {
        mComponentB = componentB;
    }

    public void doSomething()
    {
        System.out.println( "ComplexClass::doSomething()" );
    }
}
