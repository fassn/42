#!/bin/bash

sudo apt-get update
sudo apt-get -y upgrade
sudo apt-get -y install net-tools resolvconf iptables-persistent inotify-tools mailutils apache2
sudo systemctl enable apache2
