<?php
	function connect(){
		$server = "localhost";
		$user = "root";
		$pass = "fdpfdp";
		$link = mysqli_connect($server, $user, $pass);
        mysqli_select_db($link, "db_rush");
		if (!$link)
			die("Connection failed");
		else
			return ($link);
	}
	function auth($login, $passwd){
		$link = connect();
		$login = mysqli_real_escape_string($link, $login);
		$query = mysqli_query($link, "SELECT * FROM `users` WHERE login='".$login."'");
		$row = mysqli_fetch_assoc($query);
        mysqli_close($link);
		if (password_verify($passwd, $row['password']) === TRUE) {
		    if ($row['admin'])
		        return ('admin');
		    else
		        return ('member');
        }
		else {
            return (FALSE);
        }
	}

	function create($login, $passwd){
		$link = connect();
        $login = mysqli_real_escape_string($link, $login);
        $passwd = mysqli_real_escape_string($link, $passwd);
		$test = mysqli_query($link, "SELECT * FROM `users` WHERE login='".$login."'");
		if (mysqli_num_rows($test) > 0){
            mysqli_close($link);
    		return (FALSE);
		}
		else{
    		$passwd = password_hash($passwd, PASSWORD_DEFAULT);
			mysqli_query($link, "INSERT INTO `users` VALUES(NULL, '".$login."', '".$passwd."', 0)");
            mysqli_close($link);
			return (TRUE);
		}
	}

	function modif($login, $new_passwd){
        $link = connect();
        $login = mysqli_real_escape_string($link, $login);
        $new_passwd = mysqli_real_escape_string($link, $new_passwd);
		$new_passwd = password_hash($new_passwd, PASSWORD_DEFAULT);
		if (mysqli_query($link, "UPDATE `users` SET password='".$new_passwd."' WHERE login='".$login."'")){
            mysqli_close($link);
			return (TRUE);
		}
		else {
            mysqli_close($link);
            return (FALSE);
        }
	}

	function delete($login){
		$link = connect();
        $login = mysqli_real_escape_string($link, $login);
		if (mysqli_query($link, "DELETE FROM `users` WHERE login='".$login."'")) {
            mysqli_close($link);
            return (TRUE);
        }
		else {
            mysqli_close($link);
            return (FALSE);
        }
	}