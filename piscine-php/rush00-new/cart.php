<?php
    session_start();
    include_once "./includes/manage_cart.php";
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Mon panier</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="css/cart.css" />

</head>

<body>
<div>
        <div class="topnav">
            <a href="index.php">Accueil</a>
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
                            <span class="badge"><?php echo count($_SESSION['cart']['product']); ?></span>
                        </a>
                    <?php }
                }?>
            </div>
        </div>
        <div id="content">
            <table class="table">
                <h2>VOTRE PANIER</h2><br>
                <tr>
                    <th></th>
                    <td>Articles</td>
                    <td>Quantité</td>
                    <td>Prix Unitaire</td>
                </tr>
                <tr>
                    <?php
                    if (cart_init() &!is_lock())
                    {
                        $nbArticles=count($_SESSION['cart']['product']);
                        if ($nbArticles <= 0)
                        echo "<tr><td>Votre panier est vide </ td></tr>";
                        else
                        {
                            for ($i=0 ;$i < $nbArticles ; $i++)
                            {
                    ?>
                    <td class="first-td"><img src="<?php echo $_SESSION['cart']['img'][$i];?>"width="120px"/></td>
                    <td><?php echo htmlspecialchars($_SESSION['cart']['product'][$i])?><br>
                        <form action="includes/manage_cart.php?<?= "action=del_article&product=".$_SESSION['cart']['product'][$i];?>" method="POST">
                                <button class="form-button" type="submit">Supprimer</button>
                        </form></td>
                    <td>
                        <form action="includes/manage_cart.php" method="GET">
                            <input type="text" size="4" name="quantity" value="<?php echo htmlspecialchars($_SESSION['cart']['quantity'][$i])?>"><br>
                            <input type="hidden" name="product" value="<?php echo htmlspecialchars($_SESSION['cart']['product'][$i])?>">
                            <button class="form-button" type="submit" name="action" value="modif_quantity">Modifier quantite</button>
                        </form></td>
                    <td><?php echo htmlspecialchars($_SESSION['cart']['price'][$i]).' $'?></td>
                </tr>
                        <?php    } ?>
                            <tr class="total">
                                <td colspan="2"></td>
                                <td>TOTAL</td>
                                <td><?php echo global_amount().' $'?></td>
                            </tr>
                    <?php    } ?>
                <tr>
                    <td>
                    <?php if (!isset($_SESSION['logged_on_user'])){ ?>
                                <span>Pour poursuivre la commande vous de devez vous connecter</span>
                                <button class="form-button"><a href="signin.php">Me connecter</a></button>
                    <?php }else{ ?>
                                <form action="includes/manage_cart.php" method="GET">
                                    <input type="hidden" name="cart" value="<?php $_SESSION['cart']?>">
                                    <button class="form-button" type="submit" name="action" value="command">Commander</button>
                                </form>
                    <?php } ?>
                    </td>
                </tr>
                <?php   } ?>
            </table>
        </div>
    </form>
</div>
</body>

</html>