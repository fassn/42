<?php
if (!isset($_SERVER['PHP_AUTH_USER'])) {
    header("WWW-Authenticate: Basic realm=''Espace membres''");
    header('HTTP/1.0 401 Unauthorized');
}
else {
    if ($_SERVER['PHP_AUTH_USER'] === "zaz" && $_SERVER['PHP_AUTH_PW'] === "jaimelespetitsponeys") {
        $data = base64_encode(file_get_contents("../img/42.png"));
        echo "<html><body>" . PHP_EOL;
        echo "Bonjour " . $_SERVER['PHP_AUTH_USER'] . "<br />" . PHP_EOL;
        echo "<img src='data:image/png;base64," . $data . "'>" . PHP_EOL;
        echo "</body></html>" . PHP_EOL;
    }
    else {
        header("WWW-Authenticate: Basic realm=''Espace membres''");
        header('HTTP/1.0 401 Unauthorized');
        echo "<html><body>Cette zone est accessible uniquement aux membres du site</body></html>";
    }
}
