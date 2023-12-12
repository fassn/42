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
        <title>Admin/Gestion categories</title>
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
            <p class="title admin">GESTION DES CATEGORIES ET SOUS-CATEGORIES</p>
            <div class="categories"><p class="title">Categorie</p><br>
                <form action="manage_database.php" method="POST">
                    <input class="form" type="texte" name="cat" placeholder="Creer une categorie" required>
                    <button class="form-button" type="submit" name="action" value="add_cat">Ajouter</button>
                </form>
                <form action="manage_database.php" method="POST">
                    <select name="cat" class="form-control" required>
                        <option value="">--Choisissez une categorie a supprimer--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `categories`")){
                            while ($row = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row['name']; ?>"><?php echo $row['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select>
                    <button class="form-button" type="submit" name="action" value="del_cat">Supprimer</button>
                </form>
            </div><br>
            <div><p class="title">Sous-categories</p><br>
                <form action="manage_database.php" method="POST">
                    <input class="form" type="texte" name="subcat" placeholder="Creer une sous-categorie" required>
                    <button class="form-button" type="submit" name="action" value="add_subcat">Ajouter</button><br>
                </form>
                <form action="manage_database.php" method="POST">
                    <select name="subcat" class="form-control" required>
                        <option value="">--Choisissez une categorie a supprimer--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `subcategories`")){
                            while ($row = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row['name']; ?>"><?php echo $row['name']; ?></option>
                            <?php }?>
                        <?php }
                        mysqli_close($link); ?>
                    </select>
                    <button class="form-button" type="submit" name="action" value="del_subcat">Supprimer</button>
                </form>
            </div><br>
        </div>
    </body>
</html>