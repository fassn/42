<?php
session_start();
include('auth.php');
if (($_POST['submit'] === 'OK' && ($authenticated = auth($_POST['login'], $_POST['passwd'])) === true) || $_SESSION['loggued_on_user']) {
    if ($authenticated === true)
        $_SESSION['loggued_on_user'] = $_POST['login'];
    echo "<iframe name='chat' src='chat.php' width='100%' height='550px'></iframe>";
    echo "<iframe name='speak' src='speak.php' width='100%' height='50px'></iframe>";
}
else {
    $_SESSION['loggued_on_user'] = "";
    echo "ERROR\n";
}