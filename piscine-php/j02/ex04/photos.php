#!/usr/bin/php
<?php
function delete_empty_dir($str) {
    if (is_file($str)) {
        return unlink($str);
    }
    elseif (is_dir($str)) {
        $scan = glob(rtrim($str,'/').'/*');
        if (empty($scan))
            return rmdir($str);
    }
}

function get_content($url, $fp, $path) {
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_FILE, $fp);
    curl_setopt($ch, CURLOPT_TIMEOUT, 20);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
    curl_exec($ch);
    if (curl_errno($ch)) {
        echo "Couldn't download resource $url\n";
        return false;
    }
    curl_close($ch);
    return true;
}

function parse_img($html) {
    if (preg_match_all("/<img.*?src=\"(.*?)\"/s", $html, $img_path))
        return $img_path[1];
}

function get_absolute_url($img_path, $url) {
    if (strpos($img_path, "http://") !== false || strpos($img_path, "https://") !== false) {
        return $img_path;
    }
    else
        return ($url . $img_path);
}

function get_filename($img_path) {
    $filename = explode("/", $img_path);
    return ($filename[count($filename) - 1]);
}

function get_img($img_path, $url, $path) {
    foreach ($img_path as $i) {
        $full_url = get_absolute_url($i, $url);
        $filepath = $path . "/" . get_filename($i);
        if (!file_exists($filepath)) {
            $fp = fopen($filepath, "w+");
            get_content($full_url, $fp, $path);
            fclose($fp);
        }
    }
}

if ($argc == 2) {
    if (strpos($argv[1], "http://") !== false || strpos($argv[1], "https://") !== false) {
        $path = explode("/", $argv[1]);
        if (!file_exists($path[2]) && !is_dir($path[2])) {
            if (mkdir($path[2], 0777) == false) {
                echo $path[2];
                exit("Couldn't create directory");
            }
        }
    }
    else {
        exit("No http[s]:// in URL provided");
    }
    $fp = fopen("tmp", "w+");
    if (get_content($argv[1], $fp, $path[2])) {
        fseek($fp, 0);
        $html = fread($fp, filesize("tmp"));
        fclose($fp);
        $img_path = parse_img($html);
        get_img($img_path, $argv[1], $path[2]);
    }
    delete_empty_dir($path[2]);
    unlink("tmp");
}