#!/usr/bin/php
<?php
function get_data($data) {
    $users = [];
    if ($data) {
        foreach ($data as $a) {
            if ($a[2] !== "moulinette")
                $users[$a[0]]["total"] += intval($a[1]);
            else
                $users[$a[0]]["moulinette"] += intval($a[1]);
            if ($a[1] != NULL && $a[2] !== "moulinette")
                $users[$a[0]]["count"] += 1;
        }
        ksort($users);
    }
    return ($users);
}

function moyenne($users) {
    $total_notes = 0;
    $total_count = 0;
    foreach ($users as $key => $value) {
        $total_notes += $value['total'];
        $total_count += $value['count'];
    }
    if ($total_count)
        echo $total_notes / $total_count . PHP_EOL;
}

function moyenne_user($users) {
    foreach ($users as $key => $value) {
        if ($value['count'])
            echo $key . ":" . ($value['total'] / $value['count']) . PHP_EOL;
    }
}

function ecart_moulinette($users) {
    foreach ($users as $key => $value) {
        if ($value['count'])
            echo $key . ":" . ($value['total'] / $value['count'] - $value['moulinette']) . PHP_EOL;
    }
}

if ($argc == 2) {
    if ($argv[1] !== "moyenne" && $argv[1] !== "moyenne_user" && $argv[1] !== "ecart_moulinette") {
        return ;
    }
    $stdin = fopen("php://stdin", 'r');
    fgetcsv($stdin,0 , ';');
    while (($row = fgetcsv($stdin,0 , ';')) !== FALSE) {
        $data[] = $row;
    }
    $users = get_data($data);
    if ($argv[1] === "moyenne")
        moyenne($users);
    elseif ($argv[1] === "moyenne_user")
        moyenne_user($users);
    elseif ($argv[1] === "ecart_moulinette")
        ecart_moulinette($users);
}