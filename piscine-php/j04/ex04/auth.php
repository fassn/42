<?php
function auth($login, $passwd) {
    if ($login !== "" && $passwd !== "") {
        $folder = "../private";
        $filename = "passwd";
        if (($fc = file_get_contents($folder . "/" . $filename))) {
            $data = unserialize($fc);
            $hash = hash("whirlpool", $passwd);
            foreach ($data as $user) {
                if ($user['login'] == $login && $user['passwd'] == $hash)
                    return TRUE;
            }
        }
    }
    return FALSE;
}