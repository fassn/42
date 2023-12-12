<?php
    include_once "includes/function.php";

    session_start();
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>SWYO</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="css/register.css" />
    <link rel="icon" type="image/x-icon" href="favicon.ico?v=1" />
</head>

<body>
    <div>
        <a href="index.php">Retour</a>
        <div class="main">
            <div class="window">
                <div class="title"><p class="title-txt">Inscrivez-vous</p></div>
                    <form action="create.php" method="POST">
                        <?php if ($_GET['request'] === "error") { ?>
                        <input class="form invalid" type="text" name="login" placeholder="Nickname already exist"><br>
                        <input class="form invalid" type="password" name="passwd" placeholder="Please choose your password"><br>
                        <input class="form invalid" type="password" name="confirm" placeholder="Please confirm your password"><br>
                        <?php } else if ($_GET['request'] === "error_field") { ?>
                        <input class="form invalid" type="text" name="login" placeholder="Please enter your nickname"><br>
                        <input class="form invalid" type="password" name="passwd" placeholder="Please choose your password"><br>
                        <input class="form invalid" type="password" name="confirm" placeholder="Please confirm your password"><br>
                        <?php } else { ?>
                        <input class="form" type="texte" name="login" placeholder="Choose your nickname"><br>
                        <input class="form" type="password" name="passwd" placeholder="Choose your password"><br>
                        <input class="form" type="password" name="confirm" placeholder="Confirm your password"><br>
                        <?php }?>
                        <button class="form-button" type="submit" name="submit" value="OK">S'inscrire</button>
                    </form>
            </div>
        </div>
    </div>
</body>

</html>