<?php
include_once ('./includes/function.php');

session_start();
$login = $_POST["login"];
$passwd = $_POST["passwd"];
if (auth($login, $passwd) === "member"){
    $_SESSION["logged_on_user"] = $login;
    $_SESSION['role'] = 'member';
    header("location: index.php");
}else if (auth($login, $passwd) === "admin"){
    $_SESSION["logged_on_user"] = $login;
    $_SESSION['role'] = 'admin';
    header('location: index.php');
}else{
    $_SESSION["logged_on_user"] = NULL;
    header("location: index.php?request=error");
    exit();
}