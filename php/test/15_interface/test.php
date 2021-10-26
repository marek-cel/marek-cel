<?php

interface MyInterfaceA
{
    public function foo( $var );
    public function bar( $var );
}

interface MyInterfaceB
{
    public function foobar( $var );
}

class MyClass
  implements MyInterfaceA, MyInterfaceB
{
    public function foo( $var )
    {
        echo "MyClass::foo( $var ) <br/>";
    }
    
    public function bar( $var )
    {
        echo "MyClass::bar( $var ) <br/>";
    }
    
    public function foobar( $var )
    {
        echo "MyClass::foobar( $var ) <br/>";
    }
}

$mc = new MyClass();

$mc->foo( 1 );
$mc->bar( 2 );
$mc->foobar( 3 );

?>
