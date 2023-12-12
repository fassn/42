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
        <title>Admin/Gestion produits</title>
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
            <div><p class="title">GESTION DES PRODUITS</p><br>
                <p>Ajout de produit</p>
                <form action="manage_database.php" method="POST">
                    <label for="product">Nom: </label>
                    <input class="form" type="texte" name="product" placeholder="nom du produit" required><br/>
                    <label for="categorie">Categorie: </label>
                    <select name="cat" class="form-control" required>
                        <option value="">--Choisissez une categorie--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `categories`")){
                            while ($row_cat = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row_cat['name']; ?>"><?php echo $row_cat['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select><br/>
                    <label for="subcat">Sous-categorie: </label>
                    <select name="subcat" class="form-control" required>
                        <option value="">--Choisissez une sous-categorie--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `subcategories`")){
                            while ($row_subcat = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row_subcat['name']; ?>"><?php echo $row_subcat['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select><br/>
                    <label for="price">Prix: </label>
                    <input class="form" type="texte" name="price" placeholder="prix" required><br/>
                    <label for="img">Image: </label>
                    <select name="img">
                        <option value="">- Select Image -
                            <?php
                            $dirPath = scandir('../img');
                            for ($i = 2; $i < count($dirPath) ; $i++)
                                echo "<option value=\"" . trim($dirPath[$i]) . "\">" . $dirPath[$i] . "\n";
                            ?>
                    </select><br/>
                    <label for="desc">Description: </label>
                    <input class="form" style="width: 250px" type="texte" name="desc" placeholder="description" required><br/>
                    <label for="stock">Stock: </label>
                    <input class="form" type="texte" name="stock" placeholder="nombre de produit a ajouter au stock" required><br/><br/>
                    <button class="form-button" type="submit" name="action" value="add_prod">Ajouter produit</button>
                </form><br>
                <hr width="75%" color="black" align=left>
                <p>Ajouter du stock a un produit</p>
                <form action="manage_database.php" method="POST">
                    <label for="product">Produit: </label>
                    <select name="product" class="form-control" required>
                        <option value="">--Choisissez un article--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `products`")){
                            while ($row = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row['name']; ?>"><?php echo $row['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select><br/>
                    <label for="quantity">Quantite: </label>
                    <input class="form" type="texte" name="quantity" placeholder="stock a rajouter" required><br/><br/>
                    <button class="button-form" type="submit" name="action" value="add_stock">Ajouter au stock</button>
                </form><br>
                <hr width="75%" color="black" align=left>
                <p>Ajouter une sous-categorie a un produit</p>
                <form action="manage_database.php" method="POST">
                    <label for="product">Produit: </label>
                    <select name="product" class="form-control" required>
                        <option value="">--Choisissez un article--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `products`")){
                            while ($row = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row['name']; ?>"><?php echo $row['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select><br/>
                    <label for="subcategory">Sous-categorie</label>
                    <select name="subcategory" class="form-control" required>
                        <option value="">--Choisissez une sous-categorie--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `subcategories`")){
                            while ($row = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row['name']; ?>"><?php echo $row['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select><br/><br/>
                    <button class="button-form" type="submit" name="action" value="add_subcategory">Ajouter la sous-categorie</button>
                </form><br>
                <hr width="75%" color="black" align=left>
                <p>Supprimer un produit</p>
                <form action="manage_database.php" method="POST">
                    <label for="product">Produit: </label>
                    <select name="product" class="form-control" required>
                        <option value="">--Choisissez un article a supprimer--</option>
                        <?php
                        if ($result = mysqli_query($link, "SELECT `name` FROM `products`")){
                            while ($row = mysqli_fetch_assoc($result)){?>
                                <option value="<?php echo $row['name']; ?>"><?php echo $row['name']; ?></option>
                            <?php }?>
                        <?php }?>
                    </select><br/><br/>
                    <button class="form-button" type="submit" name="action" value="del_prod">Supprimer produit</button>
                </form>
            </div>
        </div>
    </body>
</html>

<?php mysqli_close($link); ?>