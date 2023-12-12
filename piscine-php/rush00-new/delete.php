<?php
include_once "./includes/function.php";

session_start();
$login = $_POST['login'];
$passwd = $_POST['passwd'];
$confirm = $_POST['confirm'];
$submit = $_POST['submit'];
if (!$login || !$passwd || !$confirm || $passwd != $confirm || $submit != "OK") {
    header("location: account.php?request=typing_error");
    exit();
}
if (auth($login, $passwd) === 'member'){
    if (delete($login) == TRUE ){
        header('location: logout.php');
        exit();
    }
    else{
        header('location: account.php?request=typing_error');
        exit();
    }
}