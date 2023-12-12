#!/usr/bin/php
<?php
$input = "";
while (true) {
    echo "Entrez un nombre: ";
    $input = trim(fgets(STDIN));
    if (feof(STDIN)) {
        echo "\n";
        break;
    }
    $invalid_input = 0;
    if (strlen($input) == 0)
    {
        echo "'" . $input . "' n'est pas un chiffre\n";
        continue;
    }
    for ($i = 0; $i < strlen($input); $i++) {
        if ($i == 0)
        {
            if (is_numeric($input[0]) === false)
            {
                if ($input[0] == "-" || $input[0] == "+") {
                    if (is_numeric($input[1]) === false)
                    {
                        echo "'" . $input . "' n'est pas un chiffre\n";
                        $invalid_input = 1;
                        break;
                    }
                }
            }
        }
        if ($i != 0 && is_numeric($input[$i]) === false) {
            echo "'" . $input . "' n'est pas un chiffre\n";
            $invalid_input = 1;
            break;
        }
    }
    $last_digit = $input[strlen($input) - 1];

    if ($invalid_input == 0 && $last_digit % 2 == 0) {
        echo "Le chiffre " . $input . " est Pair\n";
    }
    else if ($invalid_input == 0 && $last_digit % 2 != 0) {
        echo "Le chiffre " . $input . " est Impair\n";
    }
}