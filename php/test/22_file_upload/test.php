<form method="post" action="index.php" enctype="multipart/form-data">
    <input type="file" name="userfile" />
    <input type="submit" name="submit" value="SUBMIT" />
</form>

<?php

echo getcwd() . "<br/>";

if ( isset($_POST["submit"]) ) 
{
    if ( move_uploaded_file( $_FILES["userfile"]["tmp_name"], getcwd()."/upload/".basename($_FILES['userfile']['name']) ) )
    {
        echo "The file ". htmlspecialchars( basename($_FILES["userfile"]["name"]) ). " has been uploaded.";
    }
    else
    {
        echo "Sorry, there was an error uploading your file.";
    }
}

?>
