<?php
if ($_GET['action'] == "set" && $_GET['name'] !== "" && $_GET['value'] !== "") {
	setcookie($_GET['name'], $_GET['value'], time()+3600);
}
elseif ($_GET['action'] == "get" && $_GET['name'] !== "") {
	if ($_COOKIE[$_GET['name']] !== NULL) {
		echo $_COOKIE[$_GET['name']] . "\n";
	}
}
elseif ($_GET['action'] == "del" && $_GET['name'] !== "") {
	setcookie($_GET['name'], "", 0);
}