class ConcreteCreator extends Creator
{    
    @Override
    protected Product factoryMethod()
    {
        return new ConcreteProduct();
    }
}
