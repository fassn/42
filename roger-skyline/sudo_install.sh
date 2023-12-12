#!/bin/bash

if [[ $EUID -ne 0 ]]; then
	echo You must be a root user
	exit 1
else
  apt install sudo
fi
echo username to add to sudo group?
read 'username'
adduser $username
addgroup $username sudo
echo Now login as $username, please type your password
login $username
