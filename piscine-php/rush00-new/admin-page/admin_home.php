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
        <title>Admin/Home</title>
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
            <div><p class="title">BOARD</p><br>
                <div>
                    <span>Commandes en cours</span><br>
                    <tr>
                        <td>
                    <?php
                        if ($data = mysqli_query($link, "SELECT * FROM `cart`")){
                        while ($row_data = mysqli_fetch_assoc($data)){?>
                            <tr>
                                <td><span><?php echo $row_data['login'];?></span></td>
                                <td><img src='<?php echo $row_data['img_url'];?>'width="120px"/></td>
                                <td><span><?php echo $row_data['prod'];?> </span></td>
                                <td><p><?php echo $row_data['quantity'];?></p></td>
                                <td><p class="price"><?php echo $row_data['unit_price']."$";?></p></td>
                            </tr>
                            <?php }
                            mysqli_close($link);?>
                        <?php }?>
                        </td>
                    </tr>
                </div>
            </div>
        </div>
    </body>
</html>

<?php mysqli_close($link); ?>