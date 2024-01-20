<?php

class MyClass
{
    public static $staticVar = 666;

    private $var = 0;
    
    public function __construct( $var )
    {
        $this->var = $var;
    }
    
    public function __destruct() {}
    
    public function getVar()
    {
        return $this->var;
    }
    
    public function setVar( $value )
    {
        $this->var = $value;
    }
    
    private function doSomething()
    {
        // ...
    }
}

$mc = new MyClass( 7 );
echo $mc->getVar() . "<br/>";

$mc->setVar( 3 );
echo $mc->getVar() . "<br/>";

echo MyClass::$staticVar . "<br/>";

?>
