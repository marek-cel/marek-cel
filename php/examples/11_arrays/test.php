<?php

$a = array( 1, 2, 3, 4 );
print_r($a);

echo "<br/>";

$b = array( 2 => "C++" , "Java", "PHP" );
print_r($b);

echo "<br/>";

$c = array( "key1" => "value1", "key2" => "value2" );
print_r($c);

echo "<br/>";

$d = array();
$d[ 0 ] = "a";
$d[ 1 ] = "b";
$d[ 2 ] = "c";
$d[ 7 ] = "x";
print_r($d);

echo "<br/>";

$e = array();
$e[ 0 ] = "a";
$e[ 7 ] = "x";
$e[ 1 ] = "b";
print_r($e);

echo "<br/>";

$f = array();
$f[ 0 ] = "a";
$f[ "key" ] = "b";
print_r($f);

?>
