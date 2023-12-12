<?php
session_start();
include_once('auth.php');
if (($authenticated = auth($_POST['login'], $_POST['passwd'])) === true || $_SESSION['loggued_on_user']) {
    if ($authenticated === true)
        $_SESSION['loggued_on_user'] = $_POST['login'];
    if (is_admin($_SESSION['loggued_on_user']))
        $_SESSION['admin'] = TRUE;
    else
        $_SESSION['admin'] = FALSE;
    header("Location: index.php");
}
else {
    $_SESSION['loggued_on_user'] = "";
    echo 'ERROR ' . PHP_EOL;
    echo '<br>';
    echo '<a href="index.php">Retourner a la homepage</a>';
}