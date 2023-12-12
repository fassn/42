#!/usr/bin/php
<?php

if ($argc == 2) {
    $args = sscanf($argv[1], "%f %c %f %s");
    if (isset($args[0]) && $args[1] && isset($args[2]) && !$args[3]) {
        if (strcmp($args[1], "+") == 0)
            echo $args[0] + $args[2] . "\n";
        elseif (strcmp($args[1], "-") == 0)
            echo $args[0] - $args[2] . "\n";
        elseif (strcmp($args[1], "*") == 0)
            echo $args[0] * $args[2] . "\n";
        elseif (strcmp($args[1], "/") == 0)
            echo $args[0] / $args[2] . "\n";
        elseif (strcmp($args[1], "%") == 0)
            echo $args[0] % $args[2] . "\n";
    }
    else
        echo "Syntax Error\n";
} else
    echo "Incorrect Parameters\n";