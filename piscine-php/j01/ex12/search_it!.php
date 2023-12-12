#!/usr/bin/php
<?php
if ($argc > 2) {
    $value = null;
    for ($i = 2; $i < $argc; $i++) {
        $raw = explode(":", $argv[$i]);
        $array[$raw[0]] = $raw[1];
        foreach ($array as $key => $val) {
            if ($argv[1] == $key) {
                $value = $val;
            }
        }
    }
    if (isset($value))
        echo $value . "\n";
}