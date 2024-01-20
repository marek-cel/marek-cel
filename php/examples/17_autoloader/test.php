<?php

function autoloader( $class_name )
{
    require_once( 'class.' . $class_name . '.php' );
}

spl_autoload_register( 'autoloader' );

$mca = new MyClassA();
$mcb = new MyClassB();

$mca->printName();
$mcb->printName();

?>
