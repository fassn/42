<?php
include_once "./includes/function.php";

session_start();
$login = $_SESSION['logged_on_user'];
$old_passwd = $_POST['old_passwd'];
$new_passwd = $_POST['new_passwd'];
$confirm = $_POST['confirm'];
$submit = $_POST['submit'];
if (!$old_passwd || !$new_passwd || !$confirm || $new_passwd != $confirm || $submit != "OK") {
    header("location: account.php?request=error_field");
    exit();
}
if (!$old_passwd || !$new_passwd || !$confirm || $new_passwd === $old_passwd || $submit != "OK") {
    header("location: account.php?request=error_same_password");
    exit();
}
if (modif($login, $new_passwd) == TRUE){
    header('location: account.php');
    echo "Password successfully changed";
    exit();
}
else{
    header("location: account.php?request=error_field");
    exit();
}
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Compte créé</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
    <a href="index.php">Retour<a>
</body>
</html>