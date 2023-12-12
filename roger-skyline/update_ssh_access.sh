#!/bin/sh

if grep -q 'PermitRootLogin no' /etc/ssh/sshd_config; then
	echo "Root is already forbidden to login through SSH"
else
	echo "Adding PermitRootLogin on to /etc/ssh/sshd_config"
	sudo bash -c "sed -i '/#PermitRootLogin/a PermitRootLogin no' /etc/ssh/sshd_config"
fi


if grep -q 'Port 2222' /etc/ssh/sshd_config; then
	echo "SSH Port 2222 is already set."
else
	echo "Adding Port 2222 to /etc/ssh/sshd_config"
	sudo bash -c "sed -i '/#Port 22/a Port 2222' /etc/ssh/sshd_config"
fi

if grep -q 'PasswordAuthentication no' /etc/ssh/sshd_config; then
	echo "SSH key pairs authentication only is already set."
else
	echo "Adding PasswordAuthentication no to /etc/ssh/sshd_config"
	sudo bash -c "sed -i '/#PasswordAuthentication/a PasswordAuthentication no' /etc/ssh/sshd_config"
fi

echo "You will still need to setup the SSH key pairs manually"
echo "Now restarting SSH service"
sudo /etc/init.d/ssh reload
