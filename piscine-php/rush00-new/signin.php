<?php
    include_once "./includes/function.php";

    session_start();
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
        <?php if (!isset($_SESSION['logged_on_user'])){?>
            <a href="register.php">M'inscrire</a>
            <a href="index.php">Retour</a>
            <?php }?>
        </div>
    </div>
    <h2>Form on Hero Image</h2>
    <div class="bg-img">
        <form action="login.php" method="POST" class="container">
            <?php if (!isset($_GET['request'])) {?>
            <label for="pseudo"><b>Pseudo</b></label>
            <input class="form" type="text" name="login" placeholder="Saisissez votre pseudo"><br>
            <label for="psw"><b>Password</b></label>
            <input class="form" type="password" name="passwd" placeholder="Saisissez votre mot de passe"><br>
            <?php } else {?>
            <label for="pseudo"><b>Pseudo</b></label>
            <input class="form invalid" type="text" name="login" placeholder="Pseudo invalide"><br>
            <label for="psw"><b>Mot de passe</b></label>
            <input class="form invalid" type="password" name="passwd" placeholder="Mot de passe invalide"><br>
            <?php }?>
            <button class="form-button" type="submit" name="submit" value="OK">Se connecter</button>
        </form>
    </div>
</body>

</html>