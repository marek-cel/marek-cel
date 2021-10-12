<?php

function fun( &$arg )
{
    $arg = 7;
}

$var = 3;
fun( $var );

echo $var;

?>
