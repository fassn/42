<?php
    include_once "./includes/function.php";

    session_start();
    $link = connect();
    mysqli_select_db($link, "db_rush");
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>STFS maquettes</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="css/shop.css" />

</head>

<body>
    <div>
        <div class="topnav">
            <a href="index.php">Accueil</a>
            <a href="vetements.php">Vetements</a>
            <a href="accessoires.php">Accessoires</a>
            <a class="active" href="maquettes.php">Maquettes</a>
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
        <div class="tab">
            <button class="tablinks" onclick="openSubcat(event, 'Tous')" id="defaultOpen">Toutes les maquettes</button>
            <?php
            if ($result = mysqli_query($link, "SELECT DISTINCT `subcat` FROM `products` WHERE cat= 'Maquettes'")){
                while ($row = mysqli_fetch_assoc($result)){
                    $exploded = explode(',', $row['subcat']);
                    foreach ($exploded as $e)
                        $subcats[] = $e;
                }
                $subcats = array_unique($subcats);
                foreach ($subcats as $subcat) {?>
                    <button class="tablinks" onclick="openSubcat(event, '<?php echo $subcat;?>')"><?php echo $subcat;?></button>
                <?php }?>
            <?php }?>
        </div>
        <div id="Tous" class="tabcontent"> 
            <div class="element">
                <?php
                if ($data = mysqli_query($link, "SELECT * FROM `products` WHERE cat= 'Maquettes'")){
                    while ($row_data = mysqli_fetch_assoc($data)){?>
                        <div class="card">
                            <img src='<?php echo $row_data['img_url'];?>'style="width:100%"/>
                            <h1><?php echo $row_data['name'];?> </h1>
                            <p class="price"><?php echo $row_data['price']."$";?></p>
                            <form action="includes/manage_cart.php?<?= "action=add_article&product=" . $row_data['name'] . "&img=" . $row_data['img_url'] . "&price=" . $row_data['price'] . "&quantity=" . '1' ;?>" method="POST">
                                <p><button type="submit">Ajouter au panier</button></p>
                            </form>
                        </div>
                    <?php }?>
                <?php }?>
            </div>
        </div>
        <?php
        foreach ($subcats as $subcat) {?>
            <div id="<?php echo $subcat?>" class="tabcontent">
                <div class="element">
                    <?php
                    if ($result = mysqli_query($link, "SELECT DISTINCT * FROM `products` WHERE cat= 'Maquettes' AND INSTR(subcat, '".$subcat."')")){
                        while ($row = mysqli_fetch_assoc($result)) {?>
                            <div class="card">
                                <img src='<?php echo $row['img_url'];?>'style="width:100%"/>
                                <h1><?php echo $row['name'];?> </h1>
                                <p class="price"><?php echo $row['price']."$";?></p>
                                <form action="includes/manage_cart.php?<?= "action=add_article&product=" . $row_data['name'] . "&img=" . $row_data['img_url'] . "&price=" . $row_data['price'] . "&quantity=" . '1' ;?>" method="POST">
                                    <p><button type="submit">Ajouter au panier</button></p>
                                </form>
                            </div>
                        <?php }?>
                    <?php }?>
                </div>
            </div>
        <?php }
        mysqli_close($link); ?>
    </div>
    <script>
    function openSubcat(evt, subcat) {
        console.log(subcat)
        var i, tabcontent, tablinks;
        tabcontent = document.getElementsByClassName("tabcontent");
        for (i = 0; i < tabcontent.length; i++) {
            tabcontent[i].style.display = "none";
        }
        tablinks = document.getElementsByClassName("tablinks");
        for (i = 0; i < tablinks.length; i++) {
            tablinks[i].className = tablinks[i].className.replace(" active", "");
        }
        document.getElementById(subcat).style.display = "block";
        evt.currentTarget.className += " active";
    }
    document.getElementById("defaultOpen").click();
    </script>
</body>

</html>