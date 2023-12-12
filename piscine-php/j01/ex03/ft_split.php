<?php
function ft_split($string) {
    $array = explode(" ", $string);
    $array = array_filter($array);
    sort($array);
    return ($array);
}