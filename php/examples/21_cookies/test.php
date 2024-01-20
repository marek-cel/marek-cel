<form method="post" action="index.php">
    <input type="text" name="form" value="" />
    <input type="submit" value="SUBMIT" />
</form>

<?php

session_start();

if ( !empty($_POST["form"]) )
{
    setcookie( 'data', $_POST["form"], time() + (86400 * 365) ); // 86400 = 1 day
    $_COOKIE["data"] = $_POST["form"];
}

if ( !empty($_COOKIE["data"]) )
{
    echo $_COOKIE["data"] . "<br/>";
}

?>
