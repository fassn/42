<?php
include_once "./includes/function.php";

$login = $_POST['login'];
$passwd = $_POST['passwd'];
$confirm = $_POST['confirm'];
$submit = $_POST['submit'];
if (!$login || !$passwd || !$confirm || $passwd != $confirm || $submit != "OK") {
    header("location: register.php?request=error_field");
    exit();
}
if (create($login, $passwd) == TRUE ){
    header('location: signin.php');
    exit();
}
else{
    header('location: register.php?request=error');
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