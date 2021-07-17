<?php

function func1()
{
    echo "func1()";
    echo "<br />";
}

function func2( $a )
{
    echo 'func2($a) $a= ' . $a;
    echo "<br />";
}

function func3( $a, $b = 777 )
{
    echo 'func3($a,$b) $a= ' . $a . ' $b= ' . $b;
    echo "<br />";
}

func1();
FUNC1();
FuNc1();

func2( 222 );

func3( 333 );
func3( 333, 444 );

?>
