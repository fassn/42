<?php
$folder = "../private";
$filename = "chat";
if (file_exists($folder . "/" . $filename)) {
    while (($fp = fopen($folder . "/" . $filename, 'a+'))) {
        flock($fp, LOCK_SH | LOCK_EX);
        if (($fc = file_get_contents($folder . "/" . $filename))) {
            $data = unserialize($fc);
            date_default_timezone_set("Europe/Paris");
            foreach ($data as $msg) {
                echo "[" . date('G:i', $msg['time']) . "] <b>" . $msg['login'] . "</b>: " . $msg['msg'] . "<br />";
            }
        }
        fclose($fp);
        break;
    }
}