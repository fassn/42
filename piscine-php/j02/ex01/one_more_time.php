#!/usr/bin/php
<?php
function check_weekday($s) {
    return (preg_match("/(^[Ll]undi$|^[Mm]ardi$|^[Mm]ercredi$|^[Jj]eudi$|^[Vv]endredi$|^[Ss]amedi$|^[Dd]imanche$)/", $s));
}
function check_month($s, &$month_cat, &$month) {
    if (preg_match("/(^[Jj]anvier$|^[Mm]ars$|^[Mm]ai$|^[Jj]uillet$|^[Aa]o[uû]t$|^[Oo]ctobre$|^[Dd][eé]cembre$)/", $s)) {
        $month_cat = 1;
        if (preg_match("/^[Jj]anvier$/", $s))
            $month = 1;
        elseif (preg_match("/^[Mm]ars$/", $s))
            $month = 3;
        elseif (preg_match("/^[Mm]ai$/", $s))
            $month = 5;
        elseif (preg_match("/^[Jj]uillet$/", $s))
            $month = 7;
        elseif (preg_match("/^[Aa]o[uû]t$/", $s))
            $month = 8;
        elseif (preg_match("/^[Oo]ctobre$/", $s))
            $month = 10;
        elseif (preg_match("/^[Dd][eé]cembre$/", $s))
            $month = 12;
    }
    elseif (preg_match("/(^[Aa]vril$|^[Jj]uin$|^[Ss]eptembre$|^[Nn]ovembre$)/", $s))
    {
        $month_cat = 2;
        if (preg_match("/^[Aa]vril$/", $s))
            $month = 4;
        elseif (preg_match("/^[Jj]uin$/", $s))
            $month = 6;
        elseif (preg_match("/^[Ss]eptembre$/", $s))
            $month = 9;
        elseif (preg_match("/^[Nn]ovembre$/", $s))
            $month = 11;
    }
    elseif (preg_match("/^[Ff][eé]vrier$/", $s)) {
        $month_cat = 3;
        $month = 2;
    }
    else
        return 0;
    return 1;
}

function check_year($s) {
    return (preg_match("/(^19[7-9][0-9]$|^[2-9]\d{3}$)/", $s));
}

function check_leap_year($s) {
    if (($s % 4) == 0) {
        if (($s % 100) == 0) {
            if (($s % 400) == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}

function check_date($day, $month_cat, $leap) {
    if ($month_cat == 1)
        return (preg_match("/(^[1-9]$|^[12]\d$|^3[01]$)/", $day));
    elseif ($month_cat == 2)
        return (preg_match("/(^[1-9]$|^[12]\d$|^30$)/", $day));
    elseif ($month_cat == 3 && $leap)
        return (preg_match("/(^[1-9]$|^[12]\d$)/", $day));
    elseif ($month_cat == 3 && $leap == 0)
        return (preg_match("/(^[1-9]$|^1\d$|^2[0-8]$)/", $day));
    else
        return 0;
}

function check_daytime($daytime) {
    if (preg_match("/(^[01]\d$|^2[0-3]$)/", $daytime[0]))
    {
        if (preg_match("/(^[0-5]\d$)/", $daytime[1]))
            return (preg_match("/(^[0-5]\d$)/", $daytime[2]));
    }
    return 0;
}

if ($argc == 2) {
    $args = explode(" ", $argv[1]);
    $daytime = explode(":", $args[4]);
    if (count($args) != 5 || count($daytime) != 3)
        exit("Wrong Format\n");
    $leap = 0;
    $year = 0;
    $month = 0;
    $month_cat = 0;
    if (check_year($args[3])) {
        $year = 1;
        if (check_leap_year($args[3]))
            $leap = 1;
    }
    else
        exit("Wrong Format\n");
    if ($year && check_month($args[2],$month_cat, $month)) {
        if (check_date($args[1], $month_cat, $leap) == 0)
            exit("Wrong Format\n");
    }
    else
        exit("Wrong Format\n");
    if (check_weekday($args[0]) == 0)
        exit("Wrong Format\n");
    if (check_daytime($daytime) == 0)
        exit("Wrong Format\n");
    date_default_timezone_set("Europe/Paris");
    echo mktime($daytime[0], $daytime[1], $daytime[2], $month, $args[1], $args[3]) . "\n";
}
