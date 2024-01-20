<?php

class BaseClass
{
    protected $var = 0;
    
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
    
    public final function finalFunction()
    {
        echo "BaseClass::finalFunction() <br/>";
    }
}

class ChildClass extends BaseClass
{
    public function __construct( $var )
    {
        parent::__construct( $var );
    }
    
    public function newFunction()
    {
        $this->var = 144;
    }
    
    // ERROR
    //public function finalFunction() 
    //{
    //    echo "ChildClass::finalFunction() <br/>";
    //}
}

$cc = new ChildClass( 7 );
echo $cc->getVar() . "<br/>";

$cc->setVar( 3 );
echo $cc->getVar() . "<br/>";

$cc->newFunction();
echo $cc->getVar() . "<br/>";

$cc->finalFunction();

?>
