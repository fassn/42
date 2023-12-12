<?php
session_start();
$_SESSION['database'] = "on";
$admin_login = 'admin';
$admin_passwd = password_hash("admin", PASSWORD_DEFAULT);
$link = mysqli_connect("localhost", "root", "fdpfdp", "", "3306");
if (mysqli_connect_errno())
{
    $_SESSION['database'] = "";
    echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
if ((mysqli_query($link, "CREATE DATABASE IF NOT EXISTS `db_rush`;")) === false) {
    $_SESSION['database'] = "";
    exit();
}
if ((mysqli_query($link, "use db_rush")) == false) {
    $_SESSION['database'] = "";
    exit();
}
if ((mysqli_query($link, "CREATE TABLE IF NOT EXISTS `users`
(
    id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
    `login` VARCHAR(128) NOT NULL,
    `password` VARCHAR(512) NOT NULL,
    `admin` INT(1) NOT NULL
);")) === false) {
    $_SESSION['database'] = "";
    exit();
}
if ((mysqli_query($link, "CREATE TABLE IF NOT EXISTS `products`
(
    id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
    `name` VARCHAR(128) NOT NULL,
    cat VARCHAR(128) NOT NULL,
    subcat VARCHAR(128) NOT NULL,
    price DECIMAL(5, 2) NOT NULL,
    img_url VARCHAR(1024) NOT NULL,
    detail VARCHAR(2048) NOT NULL,
    stock SMALLINT(11) NOT NULL
);")) === false) {
    $_SESSION['database'] = "";
    exit();
}
if ((mysqli_query($link, "CREATE TABLE IF NOT EXISTS `categories`
(
    id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
    `name` VARCHAR(128) NOT NULL
);")) === false) {
    $_SESSION['database'] = "";
    exit();
}
if ((mysqli_query($link, "CREATE TABLE IF NOT EXISTS `subcategories`
(
    id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
    `name` VARCHAR(128) NOT NULL
);")) === false) {
    $_SESSION['database'] = "";
    exit();
}
if ((mysqli_query($link, "CREATE TABLE IF NOT EXISTS `cart`
(
    id INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
    `login` VARCHAR(128) NOT NULL,
    `prod` VARCHAR(128) NOT NULL,
    `quantity` SMALLINT(2) NOT NULL,
    `unit_price` DECIMAL(5, 2) NOT NULL,
    `total_amount` DECIMAL(10, 2) NOT NULL,
    `img_url` VARCHAR(1024) NOT NULL
);")) === false) {
    $_SESSION['database'] = "";
    exit();
}
if (mysqli_num_rows(mysqli_query($link, "SELECT * FROM `users`")) == 0)
{
    if ((mysqli_query($link, "INSERT INTO `users`
    VALUES (null, '".$admin_login."', '".$admin_passwd."', 1)
    ;")) === false) {
        $_SESSION['database'] = "";
        exit();
    }
}
mysqli_close($link);
header('location: index.php');
exit();