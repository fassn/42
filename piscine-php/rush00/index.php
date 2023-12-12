<?php
session_start();
?>
<html>
<head>
    <link rel="stylesheet" type="text/css" href="css/index.css">
    <title>SHOP LE DAIM</title>
</head>
<body>
<div id="user">
    <?php
    if ($_SESSION['loggued_on_user']) {
        echo '<div id=logged_in>';
        echo 'Bonjour ' . $_SESSION['loggued_on_user'];
        echo '(<a href="logout.php">Se deconnecter</a>)<br>';
        if ($_SESSION['admin'] === TRUE) {
            echo '<div class="admin_link">Acceder au <a href="admin.php">Panneau d\'Administration</a></div>';
        }
        echo '</div>';
    }
    else {
        echo '<div id="login">';
        echo '<form action="login.php" method="POST">';
        echo 'Login: <input type="text" name="login" value="' . $_SESSION['login'] . '">';
        echo 'Password: <input type="text" name="passwd" value="' . $_SESSION['passwd'] . '">';
        echo '<input type="submit" name="submit" value="OK">';
        echo '</form>';
        echo '<a href="index.php?show=login_create">Creer un compte</a> | <a href="index.php?show=login_modify">Modifier un mot de passe</a>';
        echo '</div>';
    }
    ?>
    <div id="cart">
        Acceder au panier: <a href="index.php?show=cart"><img src="http://www.free-icons-download.net/images/shopping-cart-logo-icon-70706.png" alt="cart logo" width="45px" /></a>
    </div>
</div>
<div id="header">
    <h1>Un style de malade</h1>
</div>
<?php
    if ($_GET['show']) {
        if ($_GET['show'] === 'login_create') {
            include ('create.html');
        }
        elseif ($_GET['show'] === 'login_modify') {
            include ('modif.html');
        }
        elseif ($_GET['show'] === 'cart') {
            include ('cart.html');
        }
    }
?>
<div id="products">
    <div id="filters"></div>
    <div id="list_products">
        <?php  ?>
    </div>
</div>
<div id="footer">
    <a href="mailto:contact@ledaim.com">Contactez-moi</a>
    <a href="https://www.instagram.com/shopledaim/">Instagram</a>
</div>
<?php include('mysql.php') ?>

</body>
</html>
