<?php
session_start();
include_once('sql_connector.php');
function get_all_products() {
    $link = mysqli_connector('root', 'fdpfdp');
    $query = mysqli_query($link, "SELECT * FROM products");
    $res =  mysqli_fetch_all($query, MYSQLI_ASSOC);
    mysqli_close($link);
    return $res;
}

include('auth.php');
if ($_SESSION['loggued_on_user'] && is_admin($_SESSION['loggued_on_user'])) {
    echo '<h1>Panneau d\'Administration du shop LE DAIM</h1>';
    echo "<h2>Bienvenue sur le panneau d'administration</h2>";
}
else {
    echo "Vous n'etes pas autorise a acceder a cette page.<br>";
    echo "Vous allez etre redirige vers la homepage dans 5 secondes<br>";
    header('refresh:5;url=index.php');
}
?>

<head>
    <title>Section Admin</title>
</head>
<html>
<body>
    <div>
        <h3>Ajouter un produit:</h3><br>
        <form method="post" action="products.php">
            Nom du produit: <input type="text" name="name" value="BOTTINE EN CUIR"><br>
            Description du produit: <input type="text" name="description" value="UNE PAIRE DE BOTTINES POUR DES SITUATIONS INCONGRUES COMME FAMILIALE"><br>
            Photo du produit: <input type="url" name="img"><br>
            Photo du produit: <input type="file" name="img"><br>
            Prix du produit: <input type="number" name="price"><br>
            <input type="submit" name="create" value="OK"><br>
        </form>
        <br><br>
        <div id="results">
            <?php
            $res = get_all_products();
            foreach ($res as $r) {
                echo '<div id=' . $r['id'] . '>';
                echo "";
                echo "</div>";
            }
            ?>
        </div>

    </div>
</body>
</html>
