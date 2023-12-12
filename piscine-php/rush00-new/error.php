<?php
session_start();

if (isset($_SESSION)) {
    echo $_SESSION['MYSQL_ERROR'];
    $_SESSION['MYSQL_ERROR'] = "";
}