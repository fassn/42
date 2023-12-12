<?php
if (array_key_exists('data', $_GET) && !empty($_GET['data'])) {
    $newid = 0;
    $fp = fopen('todo.csv', 'r+');
    while (($line = fgetcsv($fp, 0, ';')) !== FALSE) {
        if ($line[0] >= $newid)
            $newid = $line[0] + 1;
    }
    fclose($fp);
    file_put_contents('todo.csv', $newid . ';' . $_GET['data'] . PHP_EOL, FILE_APPEND);
}