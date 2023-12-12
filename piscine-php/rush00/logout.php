<?php
session_start();
$_SESSION['loggued_on_user'] = "";
$_SESSION['admin'] = FALSE;
header("Location: index.php");