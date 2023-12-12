#!/bin/bash
if grep -q 'auto enp0s3' /etc/network/interfaces; then
	echo "Configuration has already been set"
else
	echo "Setting up static ip 10.0.2.3/30"
	sudo bash -c "echo '
# The primary network interface
auto enp0s3
iface enp0s3 inet static
	address 10.0.2.3
	netmask 255.255.255.252
	broadcast 10.0.2.255
	gateway 10.0.2.2
	dns-nameservers 192.168.0.254' >> /etc/network/interfaces"
fi

if grep -q 'rc-manager=unmanaged' /etc/NetworkManager/NetworkManager.conf; then
	echo "NetworkManager is already configured properly"
else
	echo "Adding rc-manager=unmanaged to /etc/NetworkManager/NetworkManager.conf"
	sudo bash -c "sed -i '/main/a rc-manager=unmanaged' /etc/NetworkManager/NetworkManager.conf"
fi

if grep -q '192.168.0.254' /etc/resolvconf/resolv.conf.d/head; then
	echo "resolv.conf.d/head is already configured properly"
else
	echo "Adding nameserver 192.168.0.254 to /etc/resolvconf/resolv.conf.d/head"
	sudo bash -c "echo 'nameserver 192.168.0.254' >> /etc/resolvconf/resolv.conf.d/head"
fi

echo "Flushing current ip addr"
sudo ip addr flush enp0s3

echo "Now restarting networking service to apply changes..."
sudo systemctl restart networking
