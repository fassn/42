#!/usr/bin/php
<?php
if ($argc == 4) {
    $num1 = floatval(trim($argv[1], " \t"));
    $op = trim($argv[2], " \t");
    $num2 = floatval(trim($argv[3], " \t"));
    if ($num1 === NULL || $op === NULL || $num2 === NULL) {
        return ;
    }
    if (strcmp($op, "+") == 0)
        echo $num1 + $num2 . "\n";
    elseif (strcmp($op, "-") == 0)
        echo $num1 - $num2 . "\n";
    elseif (strcmp($op, "*") == 0)
        echo $num1 * $num2 . "\n";
    elseif (strcmp($op, "/") == 0)
        echo $num1 / $num2 . "\n";
    elseif (strcmp($op, "%") == 0)
        echo $num1 % $num2 . "\n";
}
else
    echo "Incorrect Parameters\n";