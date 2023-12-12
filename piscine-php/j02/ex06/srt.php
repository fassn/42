#!/usr/bin/php
<?php
function parse_srt($srt) {
    preg_match_all("/(^\d+$)\s((\d{2}:\d{2}:\d{2}.\d{3})\s-->\s\d{2}:\d{2}:\d{2}.\d{3}\s\w+)/m", $srt, $parsed);
    $results[] = array_combine($parsed[3], $parsed[2]);
    $results[] = $parsed[1];
    return $results;
}

function sort_srt($results) {
    ksort($results[0]);
    $i = 0;
    foreach ($results[0] as $key => $value) {
        echo $results[1][$i] . "\n" . $value."\n";
        $i++;
        if ($i < count($results[1]))
            echo "\n";
    }
}

if ($argc == 2) {
    if (($fp = @fopen($argv[1], 'r')) !== false) {
        $srt = fread($fp, filesize($argv[1]));
        $results = parse_srt($srt);
        sort_srt($results);
        fclose($fp);
    }
}