<?php
include_once "function.php";
session_start();
if (isset($_GET['product']))
    $product = $_GET['product'];
if (isset($_GET['price']))
    $price = $_GET['price'];
if (isset($_GET['quantity']))
    $quantity = $_GET['quantity'];
if (isset($_GET['img']))
    $img = $_GET['img'];
if (isset($_GET['action']))
    $action = $_GET['action'];

function cart_init(){
    if (!isset($_SESSION['cart'])){
        $_SESSION['cart']=array();
        $_SESSION['cart']['product'] = array();
        $_SESSION['cart']['quantity'] = array();
        $_SESSION['cart']['price'] = array();
        $_SESSION['cart']['img'] = array();
        $_SESSION['cart']['lock'] = false;
    }
    return true;
}

function is_lock(){
    if (isset($_SESSION['cart']) && $_SESSION['cart']['lock'])
        return true;
    else
        return false;
}

function delete_article($product){
    if (cart_init() && !is_lock())
    {
        $tmp=array();
        $tmp['product'] = array();
        $tmp['quantity'] = array();
        $tmp['price'] = array();
        $tmp['img'] = array();
        $tmp['lock'] = $_SESSION['cart']['lock'];
 
        for($i = 0; $i < count($_SESSION['cart']['product']); $i++)
        {
            if ($_SESSION['cart']['product'][$i] !== $product)
            {
                array_push( $tmp['product'],$_SESSION['cart']['product'][$i]);
                array_push( $tmp['quantity'],$_SESSION['cart']['quantity'][$i]);
                array_push( $tmp['price'],$_SESSION['cart']['price'][$i]);
                array_push( $tmp['img'],$_SESSION['cart']['img'][$i]);
            }
 
        }
       $_SESSION['cart'] =  $tmp;
       unset($tmp);
    }
    else
    echo "Un problème est survenu veuillez contacter l'administrateur du site.";
}

function global_amount(){
    $total=0;
    for($i = 0; $i < count($_SESSION['cart']['product']); $i++)
    {
        $total += $_SESSION['cart']['quantity'][$i] * $_SESSION['cart']['price'][$i];
    }
    return $total;
}

function delete_cart(){
    unset($_SESSION['cart']);
}

switch ($action){
    case "add_article":
        if (cart_init() && !is_lock())
        {
            $position_product = array_search($product,  $_SESSION['cart']['product']);
            if ($position_product !== false)
                $_SESSION['cart']['quantity'][$position_product] += $quantity ;
            else
            {
                array_push( $_SESSION['cart']['product'],$product);
                array_push( $_SESSION['cart']['quantity'],$quantity);
                array_push( $_SESSION['cart']['price'],$price);
                array_push( $_SESSION['cart']['img'], $img);
            }
        }
        $referer = isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '../index.php';
        header('Location: ' . $referer);
        exit();
        break;
    case "del_article":
        if (cart_init() && !is_lock())
        {
            $tmp=array();
            $tmp['product'] = array();
            $tmp['quantity'] = array();
            $tmp['price'] = array();
            $tmp['img'] = array();
            $tmp['lock'] = $_SESSION['cart']['lock'];
            for($i = 0; $i < count($_SESSION['cart']['product']); $i++)
            {
                if ($_SESSION['cart']['product'][$i] !== $product)
                {
                    array_push( $tmp['product'],$_SESSION['cart']['product'][$i]);
                    array_push( $tmp['quantity'],$_SESSION['cart']['quantity'][$i]);
                    array_push( $tmp['price'],$_SESSION['cart']['price'][$i]);
                    array_push( $tmp['img'],$_SESSION['cart']['img'][$i]);
                }       
            }
            $_SESSION['cart'] =  $tmp;
            unset($tmp);
        }
        header("location: ../cart.php");
        exit();
        break;
    case "modif_quantity":
        if (cart_init() && !is_lock())
        {
            if ($quantity > 0)
            {    
                $position_product = array_search($product,  $_SESSION['cart']['product']);
                if ($position_product !== false)
                    $_SESSION['cart']['quantity'][$position_product] = $quantity ;
            }
            else
            delete_article($product);
        }
        header("location: ../cart.php");
        exit();
        break;
    case "command":
        $link = connect();
        mysqli_select_db($link, "db_rush");
        if (cart_init())
            $_SESSION['cart']['lock'] = true;
        for ($i = 0; $i < count($_SESSION['cart']['product']); $i++){
            $total_article = $_SESSION['cart']['quantity'][$i] * $_SESSION['cart']['price'][$i];
            mysqli_query($link, "INSERT INTO `cart` VALUES (NULL, 
                           '".htmlspecialchars($_SESSION['logged_on_user'], ENT_QUOTES)."', 
                           '".htmlspecialchars($_SESSION['cart']["product"][$i], ENT_QUOTES)."', 
                           '".htmlspecialchars($_SESSION['cart']["quantity"][$i], ENT_QUOTES)."', 
                           '".htmlspecialchars($_SESSION['cart']["price"][$i], ENT_QUOTES)."', 
                           '".$total_article."', 
                           '".htmlspecialchars('../' . $_SESSION['cart']['img'][$i], ENT_QUOTES)."') ")
            or die(mysqli_error($link));
        }
        delete_cart();
        mysqli_close($link);
        header('location: ../cart.php');
        exit();
        break;
}