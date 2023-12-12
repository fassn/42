<?php
    include_once "./includes/function.php";

    session_start();
    if (!isset($_SESSION['database'])){
        header('location: install.php');
    }
    $link = connect();
    mysqli_select_db($link, "db_rush");
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Star Trek Fan Shop</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="css/shop.css" />

</head>

<body>
    <div>
        <div class="topnav">
            <a class="active" href="index.php">Accueil</a>
            <a href="vetements.php">Vetements</a>
            <a href="accessoires.php">Accessoires</a>
            <a href="maquettes.php">Maquettes</a>
            <div class="auth">

                <?php if (!isset($_SESSION['logged_on_user'])){?>
                <a href="register.php">M'inscrire</a>
                <a href="signin.php">Me connecter</a>
                <a href="cart.php" class="notification">
                    <img src="img/bag.png" width="70px"/>
                    <span class="badge"><?php echo count($_SESSION['cart']['product']); ?></span>
                </a>
                <?php
                }else{
                    if ($_SESSION['role'] === 'admin' ){?>
                        <a href="admin-page/admin_home.php">Panneau d'administration</a>
                        <a href="logout.php">Me deconnecter</a>
                        <a href="cart.php" class="notification">
                            <img src="img/bag.png" width="60px"/>
                            <span class="badge"><?php echo count($_SESSION['cart']['product']); ?></span>
                        </a>
                        <?php
                    }else{ ?>
                        <a href="account.php">Mon compte</a>
                        <a href="logout.php">Me deconnecter</a>
                        <a href="cart.php" class="notification">
                            <img src="img/bag.png" width="60px"/>
                            <p><?php echo (count($_SESSION['cart']['product']));
                                ?></p>
                            <span class="badge"><?php echo count($_SESSION['cart']['product']); ?></span>
                        </a>
                    <?php }
                }?>
            </div>
        </div>
        <div style="padding-left:16px">
            <?php
            if ($data = mysqli_query($link, "SELECT * FROM `products` ORDER BY RAND() LIMIT 3")){
                while ($row_data = mysqli_fetch_assoc($data)){?>
                    <div class="card" id="carousel">
                        <img src='<?php echo $row_data['img_url'];?>'style="width:100%"/>
                        <h1><?php echo $row_data['name'];?> </h1>
                        <p class="price"><?php echo $row_data['price']."$";?></p>
                        <form action="./includes/manage_cart.php?<?= "action=add_article&product=" . $row_data['name'] . "&img=" . $row_data['img_url'] . "&price=" . $row_data['price'] . "&quantity=" . '1' ;?>" method="POST">
                            <p><button type="submit">Ajouter au panier</button></p>
                        </form>
                    </div>
                <?php }?>
            <?php }
            mysqli_close($link); ?>
        </div>
    </div>
</body>

</html>