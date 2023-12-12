#!/bin/bash

if [ ! -f /var/log/update_script.log ]; then
	sudo bash -c "touch /var/log/update_script.log";
fi

# Putting 10s sleep to give the time for the network to be up
sleep 10
sudo bash -c 'apt-get update | while IFS= read -r line; do echo "$(date) $line"; done  >> /var/log/update_script.log'
sudo bash -c 'apt-get -y upgrade | while IFS= read -r line; do echo "$(date) $line"; done >> /var/log/update_script.log'
sudo apt-get -y autoremove
