<?php
    include_once "../includes/function.php";

    session_start();
    if ($_SESSION['role'] !== 'admin'){
        header('location: ../index.php');
        exit();
    }
    $link = connect();
    mysqli_select_db($link, "db_rush");
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>Admin/Gestion utilisateurs</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" type="text/css" media="screen" href="../css/admin.css" />
        <link rel="icon" type="image/x-icon" href="../img/favicon-admin.png" />
    </head>
    <body>
        <div class="sidenav">
            <a href="admin_home.php">Board</a>
            <a href="admin_categories.php">Categories</a>
            <a href="admin_products.php">Produits</a>
            <a href="admin_users.php">Utilisateurs</a>
        </div>
        <div class="footer-sidenav">
            <a href="../index.php">Retour<a>
            <a href="../logout.php">Logout</a>
        </div>
        <div class="main">
            <div><p class="title">UTILISATEURS</p><br>
                <form action="manage_database.php" method="POST">
                    <input class="form" style="width: 250px" type="texte" name="user" placeholder="nom de l'utilisateur a supprimer" required>
                    <button class="form-button"  type="submit" name="action" value="del_user">Supprimer l'utilisateur</button>
                </form>
            </div>
        </div>
    </body>
</html>