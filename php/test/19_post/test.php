<form method="post" action="index.php">
    <input type="text" name="form" value="" />
    <input type="submit" value="SUBMIT" />
</form>

<?php

if ( !empty($_POST["form"]) )
{
    echo $_POST["form"] . "<br/>";
}

?>
