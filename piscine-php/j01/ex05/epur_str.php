#!/usr/bin/php
<?php
if ($argc == 2) {
    $string = trim($argv[1]);
    $string = preg_replace('/ +/', ' ', $string);
    echo $string . "\n";
}