<?php

function fun( $x, $y = 7 )
{
    return $x + $y;
}

echo fun( 3 ) . "<br/>";
echo fun( 3, 3 ) . "<br/>";

?>
