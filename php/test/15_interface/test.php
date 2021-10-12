<?php

interface MyInterface
{
    public function foo( $var );
    public function bar( $var );
}

class MyClass implements MyInterface
{
    public function foo( $var )
    {
        echo "MyClass::foo( $var ) <br/>";
    }
    
    public function bar( $var )
    {
        echo "MyClass::bar( $var ) <br/>";
    }
}

$mc = new MyClass();

$mc->foo( 1 );
$mc->bar( 2 );

?>
