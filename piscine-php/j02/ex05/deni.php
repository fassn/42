#!/usr/bin/php
<?php
if ($argc == 3) {
    $lookup_key = $argv[2];
    if (($fp = fopen($argv[1], 'r+')) !== false) {
        if (($header = fgetcsv($fp, 0, ';')) !== false) {
            $i = 0;
            foreach ($header as $key => $value) {
                $$value = array();
                if ($value === $lookup_key)
                    $index = $i;
                $i++;
            }
            if ($index === NULL)
                return ;
        }
        while (($line = fgetcsv($fp, 0, ';')) !== false) {
            $i = 0;
            foreach ($header as $value) {
                ${$value}[$line[$index]] = $line[$i];
                $i++;
            }
        }
        fclose($fp);
    }
    while (true) {
        echo "Entrez votre commande: ";
        $input = trim(fgets(STDIN));
        try {
            eval($input);
        }
        catch(ParseError $p) {
            echo "PHP Parse error: " . $p->getMessage() . PHP_EOL;
        }
        if (feof(STDIN)) {
            echo "\n";
            break;
        }
    }
}