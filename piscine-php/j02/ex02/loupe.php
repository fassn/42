#!/usr/bin/php
<?php
function parse_links($s) {
    $result = array();
    preg_match_all("/<a.*?<\/a>/s", $s, $a);
    foreach ($a[0] as $el) {
        preg_match_all("/title=\"(.*?)\"|>(.*?)</s", $el, $text);
        for ($i = 1; $i < count($text); $i++) {
            $text[$i] = array_filter($text[$i]);
            if (!empty($text[$i])) {
                foreach ($text[$i] as $t)
                    $result[] = $t;
            }
        }
    }
    if (!empty($result))
        return $result;
}

function get_content($path) {
    $file = fopen($path, 'r');
    return (fread($file, filesize($path)));
}

if ($argc == 2) {
    $content = get_content($argv[1]);
    $results = parse_links($content);
    foreach ($results as $result) {
        $content = str_ireplace($result, strtoupper($result), $content);
    }
    echo $content;
}