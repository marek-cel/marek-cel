<?php

abstract class AbstractClass
{
    public function foo()
    {
        echo "AbstractClass::foo() <br/>";
    }
    
    public abstract function bar();
}

class ConcreteClass extends AbstractClass
{
    public function bar()
    {
        echo "ConcreteClass::bar() <br/>";
    }
}

//$ac = new AbstractClass(); // ERROR
$cc = new ConcreteClass();

$cc->foo();
$cc->bar();

?>
