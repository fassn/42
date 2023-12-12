<?php
function check_if_login_exists($array) {
	foreach ($array as $login) {
		foreach ($login as $key => $value) {
			if ($key == 'login' && $value == $_POST['login'])
				return true;
		}
	}
	return false;
}

if ($_POST['submit'] === "OK") {
	if ($_POST['login'] !== "" && $_POST['passwd'] !== "") {
		$folder = "../private";
		$filename = "passwd";
		$hash = hash("whirlpool", $_POST['passwd']);
		$user['login'] = $_POST['login'];
		$user['passwd'] = $hash;

		if (file_exists($folder) === false)
			mkdir($folder);
		if (file_exists($folder . "/" . $filename)) {
			$fc = file_get_contents($folder . "/" . $filename);
			$data =  unserialize($fc);
			if (check_if_login_exists($data)) {
				echo "ERROR\n";
				exit();
			}
			else {
				$data[] = $user;
				$serialized = serialize($data);
				file_put_contents($folder . "/" . $filename, $serialized);
			}
		}
		else {
			$data[] = $user;
			$serialized = serialize($data);
			file_put_contents($folder . "/" . $filename, $serialized);
		}
		echo "OK\n";
		header("Location: index.html");
	}
	else
	    echo "ERROR\n";
}
else
    echo "ERROR\n";