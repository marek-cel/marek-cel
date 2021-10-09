public class Director
{
    private Builder mBuilder = null;

    public Director( Builder builder )
    {
        mBuilder = builder;
    }

    public void construct()
    {
        mBuilder.buildProduct();
        mBuilder.buildPartA();
        mBuilder.buildPartB();

        ComplexClass cc = mBuilder.getProduct();

        cc.doSomething();
    }
}
