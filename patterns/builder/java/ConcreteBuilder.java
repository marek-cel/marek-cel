public class ConcreteBuilder extends Builder
{
    private ComplexClass mProduct = null;

    public void buildProduct()
    {
        System.out.println( "ConcreteBuilder::buildProduct()" );
        mProduct = new ComplexClass();
    }

    public void buildPartA()
    {
        System.out.println( "ConcreteBuilder::buildPartA()" );
        mProduct.addComponentA( new ComponentA() );
    }

    public void buildPartB()
    {
        System.out.println( "ConcreteBuilder::buildPartB()" );
        mProduct.addComponentB( new ComponentB() );
    }

    public ComplexClass getProduct()
    {
        return mProduct;
    }
}
