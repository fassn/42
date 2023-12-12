<script langage="javascript">top.frames['chat'].location = 'chat.php';</script>
<?php
session_start();
if ($_SESSION['loggued_on_user']) {
    echo "<form action='speak.php' method='post'>";
    echo "<input type='text' name='msg' value=''>";
    echo "<input type='submit' name='submit' value='OK'>";
    echo "</form>";
}
else
    echo "ERROR\n";

if ($_POST['submit'] == "OK" && $_POST['msg'] && $_SESSION['loggued_on_user']) {
    $folder = "../private";
    $filename = "chat";
    $msg['login'] = $_SESSION['loggued_on_user'];
    $msg['msg'] = $_POST['msg'];
    $msg['time'] = time();
    if (file_exists($folder) === false)
        mkdir($folder);
    if (file_exists($folder . "/" . $filename)) {
        while (($fp = fopen($folder . "/" . $filename, 'a+'))) {
            flock($fp, LOCK_SH | LOCK_EX);
            if (($fc = file_get_contents($folder . "/" . $filename))) {
                $data = unserialize($fc);
                $data[] = $msg;
                $serialized = serialize($data);
                file_put_contents($folder . "/" . $filename, $serialized);
            }
            fclose($fp);
            break;
        }
    }
    else {
        $data[] = $msg;
        $fp = fopen($folder . "/" . $filename, 'a+');
        flock($fp, LOCK_SH | LOCK_EX);
        $serialized = serialize($data);
        file_put_contents($folder . "/" . $filename, $serialized);
        fclose($fp);
    }
}
?>