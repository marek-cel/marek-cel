<a href="index.php?data=value">CLICK ME</a>
<br/>

<form method="get" action="index.php">
    <input type="text" name="form" value="" />
    <input type="submit" value="SUBMIT" />
</form>

<?php

if ( !empty($_GET["data"]) )
{
    echo $_GET["data"] . "<br/>";
}

if ( !empty($_GET["form"]) )
{
    echo $_GET["form"] . "<br/>";
}

?>
