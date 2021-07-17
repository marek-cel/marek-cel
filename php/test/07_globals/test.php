<?php

function fun1()
{
    echo $GLOBALS[ 'zmienna1' ] . "<br/>";
}

function fun2()
{
    global $zmienna1;
    echo $zmienna1 . "<br/>";
}

global $zmienna1;
$zmienna1 = 3;

fun1();
fun2();

$GLOBALS[ 'zmienna1' ] = 7;

fun1();
fun2();

?>
