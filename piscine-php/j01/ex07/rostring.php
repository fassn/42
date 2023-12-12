#!/usr/bin/php
<?php
function ft_split($string) {
    $array = explode(" ", $string);
    $array = array_filter($array);
    return ($array);
}

if (strlen($argv[1]) > 0 && strlen(trim($argv[1])) == 0)
    return ;
if (isset($argv[1]) && $argv[1] !== "") {
    $string = trim($argv[1]);
    $string = preg_replace('/ +/', ' ', $string);
    $array = ft_split($string);
    $len_array = count($array);
    $last_word = $array[0];
    for ($i = 1; $i < $len_array; $i++) {
        echo $array[$i] . " ";
    }
    echo $last_word . "\n";
}