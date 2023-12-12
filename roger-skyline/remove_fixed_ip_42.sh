#!/bin/bash

if grep -q 'auto enp0s3' /etc/network/interfaces; then
	sudo sed -i '/\# The primary network interface/d' /etc/network/interfaces
	sudo sed -i '/auto enp0s3/d' /etc/network/interfaces
	sudo sed -i '/iface enp0s3 inet static/d' /etc/network/interfaces
	sudo sed -i '/address 10.0.2.3/d' /etc/network/interfaces
	sudo sed -i '/netmask 255.255.255.252/d' /etc/network/interfaces
	sudo sed -i '/broadcast 10.0.2.255/d' /etc/network/interfaces
	sudo sed -i '/gateway 10.0.2.2/d' /etc/network/interfaces
	sudo sed -i '/dns-domain 42.fr/d' /etc/network/interfaces
	sudo sed -i '/dns-search 42.fr/d' /etc/network/interfaces
	sudo sed -i '/dns-nameservers 10.51.1.42/d' /etc/network/interfaces
	sudo sed -i '/dns-nameservers 10.51.1.43/d' /etc/network/interfaces
else
	echo 'nothing to remove in /etc/network/interfaces'
fi

if grep -q 'rc-manager=unmanaged' /etc/NetworkManager/NetworkManager.conf; then
	sudo sed -i '/rc-manager=unmanaged/d' /etc/NetworkManager/NetworkManager.conf
else
	echo 'nothing to remove in /etc/NetworkManager/NetworkManager.conf'
fi

if grep -q '10.51.1.42' /etc/resolvconf/resolv.conf.d/head; then
	sudo sed -i '/10.51.1.42/d' /etc/resolvconf/resolv.conf.d/head
	sudo sed -i '/domain 42.fr/d' /etc/resolvconf/resolv.conf.d/head
	sudo sed -i '/search 42.fr/d' /etc/resolvconf/resolv.conf.d/head
else
	echo "nothing to remove /etc/resolvconf/resolv.conf.d/head"
fi

echo "Flushing current ip addr"
sudo ip addr flush enp0s3

echo "Now restarting networking service to apply changes..."
sudo dhclient
sudo systemctl restart networking
