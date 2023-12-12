#!/usr/bin/php
<?php

function ft_split($string) {
    $array = explode(" ", $string);
    $array = array_filter($array);
    return ($array);
}

if ($argc > 1) {
    $array = array();
    for ($i = 1; $i < $argc; $i++) {
        $array = ft_split($argv[$i]);
        foreach ($array as $a)
            $result[] = $a;
    }
    if (count($result) > 0)
    {
        sort($result);
        foreach ($result as $r)
            echo $r . "\n";
    }
}