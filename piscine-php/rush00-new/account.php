<?php
    session_start();
    include_once "includes/function.php";
    $link = connect();
    mysqli_select_db($link, "db_rush");
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>SWYO</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="css/signin.css" />
    <link rel="icon" type="image/x-icon" href="favicon.ico?v=1" />
</head>

<body>
    <div>
        <div class="topnav">
                <?php if ($_SESSION['logged_on_user'] == ""){?>
                <a href="register.php">M'inscrire</a>
                <a href="signin.php">Me connecter</a>
                <?php
                }else{
                    if ($_SESSION['admin'] == TRUE){?>
                        <a href="admin-page/admin_home.php">Panneau d'administration</a><br>
                        <a href="layout.php">Gestion du style</a><br>
                        <a href="logout.php">Me deconnecter</a><br>
                        <?php
                    }else{ ?>
                        <a href="index.php">Retour</a>
                        <a href="logout.php">Me deconnecter</a>
                    <?php }
                }?>
        </div>
    </div>
    <div>
        <div class="container-left">
            <span>Votre derniere commande</span><br>
            <tr>
            <?php
                $login = $_SESSION['logged_on_user'];
                if ($data = mysqli_query($link, "SELECT * FROM `cart` WHERE login= '$login'")){
                while ($row_data = mysqli_fetch_assoc($data)){?>
                    <tr>
                        <td><img src='<?php echo $row_data['img_url'];?>'width="120px"/></td>
                        <td><h1><?php echo $row_data['prod'];?> </h1></td>
                        <td><p><?php echo $row_data['quantity'];?></p></td>
                        <td><p class="price"><?php echo $row_data['unit_price']."$";?></p></td>
                    </tr>
                    <?php }?>
                <?php }
                mysqli_close($link); ?>
            </tr>
        </div>
        <div class="container">
            <div class="title"><p class="title-txt">Changez le mot de passe</p></div>
                <form action="modif.php" method="POST">
                    <?php if ($_GET['request'] === "error_field") {?>
                        <input class="form invalid" type="password" name="old_passwd" placeholder="Please enter your actual password"><br>
                        <input class="form invalid" type="password" name="new_passwd" placeholder="Please enter your new password"><br>
                        <input class="form invalid" type="password" name="confirm" placeholder="Please confirm your new password"><br>
                    <?php }else if ($_GET['request'] === "error_same_password") {?>
                        <input class="form invalid" type="password" name="old_passwd" placeholder="Please enter your actual password"><br>
                        <input class="form invalid" type="password" name="new_passwd" placeholder="Please choose a different password"><br>
                        <input class="form invalid" type="password" name="confirm" placeholder="Please confirm your new password"><br>
                    <?php } else {?>
                        <input class="form" type="password" name="old_passwd" placeholder="Enter your actual password"><br>
                        <input class="form" type="password" name="new_passwd" placeholder="Enter your new password"><br>
                        <input class="form" type="password" name="confirm" placeholder="Confirme your new password"><br>
                    <?php }?>
                    <button class="form-button" type="submit" name="submit" value="OK">Changer mon mot de passe</button>
                </form><br>
            <div class="title"><p class="title-text">Supprimer mon compte</p></div>
                <form action="delete.php" method="POST">
                    <?php if ($_GET['request'] === "typing_error") {?>
                        <input class="form invalid" type="texte" name="login" placeholder="Veuillez entrer votre pseudo"><br>
                        <input class="form invalid" type="password" name="passwd" placeholder="Veuillez entrer votre mot de passe"><br>
                        <input class="form invalid" type="password" name="confirm" placeholder="Veuillez confirmez votre mot de passe"><br>
                    <?php }else{?>
                        <input class="form invalid" type="texte" name="login" placeholder="Entrez votre pseudo"><br>
                        <input class="form invalid" type="password" name="passwd" placeholder="Entrez votre mot de passe"><br>
                        <input class="form invalid" type="password" name="confirm" placeholder="Confirmez votre mot de passe"><br>
                    <?php } ?>
                    <button class="form-button" type="submit" name="submit" value="OK">Supprimer mon compte</button>
                </form>
        </div>
    </div>
</body>
</html>