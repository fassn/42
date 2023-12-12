<?php
if ($_POST['submit'] === "OK") {
    if ($_POST['login'] && $_POST['oldpw'] && $_POST['newpw']) {
        $hash_oldpw = hash("whirlpool", $_POST['oldpw']);
        $hash_newpw = hash("whirlpool", $_POST['newpw']);
        $folder = "../private";
        $filename = "passwd";
        if (file_exists($folder . "/" . $filename)) {
            if (($fc = file_get_contents($folder . "/" . $filename))) {
                $data = unserialize($fc);
                $match = 0;
                foreach ($data as &$user) {
                    if ($user['login'] == $_POST['login']) {
                        if ($user['passwd'] == $hash_oldpw) {
                            $user['passwd'] = $hash_newpw;
                            $match = 1;
                            break;
                        }
                    }
                }
                if ($match) {
                    $serialized  = serialize($data);
                    file_put_contents($folder . "/" . $filename, $serialized);
                    echo "OK\n";
                    header("Location: index.html");
                }
            }
        }
    }
}
echo "ERROR\n";