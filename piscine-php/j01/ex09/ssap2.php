#!/usr/bin/php
<?php
function print_sp_array($array)
{
    foreach ($array as $string)
        echo $string . PHP_EOL;
}

function ft_split($str)
{
    $result = array();
    $array = mb_split(" ", $str);
    foreach ($array as $string)
    {
        if ($string != "")
            $result[] = $string;
    }
    return $result;
}

function cmp_sort($a, $b)
{
    $i = 0;
    $s = "abcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~";
    while ($i < strlen($a) && $i < strlen($b))
    {
        $pa = strpos($s, strtolower($a[$i]));
        $pb = strpos($s, strtolower($b[$i]));
        if ($pa != $pb)
            break ;
        $i++;
    }
    if ($pa === $pb)
        return 0;
    if ($pa > $pb)
        return 1;
    else
        return -1;
}

$array = array();
for	($i = 1; $i < $argc; $i++)
    if ($argv[$i] != NULL)
        $array = array_merge($array, ft_split($argv[$i]));
usort($array, "cmp_sort");
print_sp_array($array);