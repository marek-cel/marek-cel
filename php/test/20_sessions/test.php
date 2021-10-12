<form method="post" action="index.php">
    <input type="text" name="form" value="" />
    <input type="submit" value="SUBMIT" />
</form>

<?php

session_start();

if ( !empty($_POST["form"]) )
{
    $_SESSION["data"] = $_POST["form"];
}

if ( !empty($_SESSION["data"]) )
{
    echo $_SESSION["data"] . "<br/>";
}

?>
