<?php
    include_once "../includes/function.php";

    session_start();
    if (!isset($_SESSION['role']) || $_SESSION['role'] !== 'admin'){
        header('location: ./index.php');
        exit();
    }
    $link = connect();
    mysqli_select_db($link, "db_rush");
    $action = $_POST['action'];

    switch($action){
        case "add_cat":
            $cat = mysqli_real_escape_string($link, htmlspecialchars($_POST['cat']));
            if (!$cat || strlen($cat) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'String is too long or empty.';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "INSERT INTO `categories` VALUES(NULL, '".$cat."')");
            mysqli_close($link);
            header('location: admin_categories.php');
            break;
        case "del_cat":
            $cat = mysqli_real_escape_string($link, htmlspecialchars($_POST['cat']));
            if (!$cat || strlen($cat) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'String is too long or empty.';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "DELETE FROM `categories` WHERE `name`='".$cat."'");
            mysqli_close($link);
            header('location: admin_categories.php');
            break;
        case "add_subcat":
            $subcat = mysqli_real_escape_string($link, htmlspecialchars($_POST['subcat']));
            if(!$subcat || strlen($subcat) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'String is too long or empty.';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "INSERT INTO `subcategories` VALUES(NULL, '".$subcat."')");
            mysqli_close($link);
            header('location: admin_categories.php');
            break;
        case "del_subcat":
            $subcat = mysqli_real_escape_string($link, htmlspecialchars($_POST['subcat']));
            if (!$subcat || strlen($subcat) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'String is too long or empty.';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "DELETE FROM `subcategories` WHERE `name`='".$subcat."'");
            mysqli_close($link);
            header('location: admin_categories.php');
            break;
        case "add_prod":
            $cat = mysqli_real_escape_string($link, htmlspecialchars($_POST['cat'], ENT_QUOTES));
            $subcat = mysqli_real_escape_string($link, htmlspecialchars($_POST['subcat'], ENT_QUOTES));
            $name = mysqli_real_escape_string($link, htmlspecialchars($_POST['product'], ENT_QUOTES));
            $_price = mysqli_real_escape_string($link, htmlspecialchars($_POST['price'], ENT_QUOTES));
            if (($price = filter_var($_price, FILTER_VALIDATE_FLOAT)) === false) {
                $_SESSION['MYSQL_ERROR'] = 'Price is not well formatted';
                header('location: ../error.php');
                break;
            }
            $img = mysqli_real_escape_string($link, htmlspecialchars($_POST['img'], ENT_QUOTES));
            $desc = mysqli_real_escape_string($link, htmlspecialchars($_POST['desc'], ENT_QUOTES));
            $_stock = mysqli_real_escape_string($link, htmlspecialchars($_POST['stock'], ENT_QUOTES));
            if (($stock = filter_var($_stock, FILTER_VALIDATE_INT)) === false) {
                $_SESSION['MYSQL_ERROR'] = 'Stock is not well formatted';
                header('location: ../error.php');
                break;
            }
            if (!$name || strlen($name) > 128 || !$cat || strlen($cat) > 128 || !$subcat || strlen($subcat) > 128 || $price < 0 || $price > 99999.99 || !$img || strlen($img) > 1024 || !$desc || strlen($desc) > 2048 || $stock < 0 || $stock > 32000) {
                $_SESSION['MYSQL_ERROR'] = 'There was problem with one of the entries';
                header('location: ../error.php');
                break;
            }
            $query = "INSERT INTO `products` VALUES (NULL, '".$name."', '".$cat."', '".$subcat."', '".$price."', '".'img/'.$img."', '".$desc."', '".$stock."');";
            mysqli_query($link, $query);
            mysqli_close($link);
            header('location: admin_products.php');
            break;
        case "add_stock":
            $name = mysqli_real_escape_string($link, htmlspecialchars($_POST['product'], ENT_QUOTES));
            $_quantity = mysqli_real_escape_string($link, htmlspecialchars($_POST['quantity'], ENT_QUOTES));
            if (($quantity = filter_var($_quantity, FILTER_VALIDATE_INT)) === false) {
                $_SESSION['MYSQL_ERROR'] = 'Quantity is not a positive number';
                header('location: ../error.php');
                break;
            }
            if (!$name || $quantity <= 0 || $quantity > 32000) {
                $_SESSION['MYSQL_ERROR'] = 'There is a problem in the inputs';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "UPDATE `products` SET stock= stock + '".$quantity."' WHERE name='".$name."'");
            mysqli_close($link);
            header('location: admin_products.php');
            break;
        case "add_subcategory":
            $name = mysqli_real_escape_string($link, htmlspecialchars($_POST['product'], ENT_QUOTES));
            $subcategory = mysqli_real_escape_string($link, htmlspecialchars($_POST['subcategory'], ENT_QUOTES));
            if (!$name || strlen($name) > 128 || !$subcategory || strlen($subcategory) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'One of the inputs is NULL or too long';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "UPDATE `products` SET subcat=IF(INSTR(subcat, '$subcategory') = 0, CONCAT_WS(',', subcat, '$subcategory'), subcat) WHERE name='".$name."'");
            mysqli_close($link);
            header('location: admin_products.php');
            break;
        case "del_prod":
            $name = mysqli_real_escape_string($link, htmlspecialchars($_POST['product'], ENT_QUOTES));
            if (!$name || strlen($name) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'Product name is NULL or too long';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "DELETE FROM `products` WHERE `name`='".$name."'");
            mysqli_close($link);
            header('location: admin_products.php');
            break;
        case "del_user":
            $user = mysqli_real_escape_string($link, htmlspecialchars($_POST['user'], ENT_QUOTES));
            if (!$user || strlen($user) > 128) {
                $_SESSION['MYSQL_ERROR'] = 'user is NULL or too long';
                header('location: ../error.php');
                break;
            }
            mysqli_query($link, "DELETE FROM `users` WHERE `login`='".$user."'");
            mysqli_close($link);
            header('location: admin_users.php');
            break;
    }
    exit();