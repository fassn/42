<?php
if (file_exists('todo.csv')) {
    $fp = fopen('todo.csv', 'r');
    while (($line = fgetcsv($fp, 0, ';')) !== FALSE) {
        $data[$line[0]] = $line[1];
    }
    fclose($fp);
    echo json_encode($data);
}