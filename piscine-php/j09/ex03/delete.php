<?php
$data = '';
if (file_exists("todo.csv") && array_key_exists('id', $_GET) && !empty($_GET['id'])) {
    $fp = fopen('todo.csv', 'r+');
    while (($line = fgetcsv($fp, 0, ';')) !== FALSE) {
        if ($line[0] != $_GET['id']) {
            $data .= $line[0] . ';' . $line[1] . PHP_EOL;
        }
    }
    fclose($fp);
    file_put_contents('todo.csv', $data);
}