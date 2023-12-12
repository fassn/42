<?php
include_once('sql_connector.php');
function auth($login, $passwd) {
    $link = mysqli_connector('root', 'fdpfdp');
    $escaped_login = mysqli_real_escape_string($link, $login);
    $query = mysqli_query($link, "SELECT pw FROM users WHERE name='$escaped_login'");
    $res = mysqli_fetch_array($query, MYSQLI_ASSOC);
    mysqli_close($link);
    if (password_verify($passwd, $res['pw']))
        return TRUE;
    return FALSE;
}

function is_admin($login) {
    $link = mysqli_connector('root', 'fdpfdp');
    $escaped_login = mysqli_real_escape_string($link, $login);
    $query = mysqli_query($link, "SELECT privilege FROM users WHERE name ='$escaped_login'");
    $res = mysqli_fetch_array($query, MYSQLI_ASSOC);
    mysqli_close($link);
    if ($res['privilege'] === 'admin')
        return TRUE;
    else
        return FALSE;
//    $stmt = mysqli_prepare("SELECT privilege FROM users WHERE name = ?");
//    mysqli_stmt_bind_param($stmt, 's', $login);
//    mysqli_stmt_execute($stmt);

}