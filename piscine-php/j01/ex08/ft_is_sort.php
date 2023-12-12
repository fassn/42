<?php
function ft_is_sort(array $tab){
    $sorted = $tab;
    $rsorted = $tab;
    sort($sorted);
    if ($sorted === $tab)
        return (TRUE);
    rsort($rsorted);
    if ($rsorted === $tab)
        return (TRUE);
    return (FALSE);
}