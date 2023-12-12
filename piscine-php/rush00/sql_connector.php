<?php
function mysqli_connector($login, $pw) {
    $link = mysqli_connect("localhost", $login, $pw, "ledaim");
    if (mysqli_connect_errno()) {
        echo "Echec lors de la connexion à MySQL : " . mysqli_connect_error();
    }
    return $link;
}