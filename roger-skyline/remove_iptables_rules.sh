#!/bin/sh

sudo iptables -F
sudo iptables -t mangle -F
sudo iptables -t raw -F
sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -X Lv
sudo iptables -X port-scanning
### Make the iptables rules persistent after reboot
sudo bash -c "iptables-save > /etc/iptables/rules.v4"
sudo bash -c "sed -i '/# Configuration suggested and added from https:\/\/javapipe.com\/blog\/iptables-ddos-protection/,/net.ipv4.conf.all.rp_filter = 1/d' /etc/sysctl.conf"
sudo bash -c "sed -i '/# Configuration suggested and added from https:\/\/geekeries.org\/2017\/12\/configuration-avancee-du-firewall-iptables/,/net.netfilter.nf_conntrack_max=200000/d' /etc/sysctl.conf"
if [ -f /etc/modprobe.d/nf_conntrack.conf ]; then
	echo Removing /etc/modprobe.d/nf_conntrack.conf configuration file
	sudo rm /etc/modprobe.d/nf_conntrack.conf
else	
	echo Nothing to remove in /etc/modprobe.d
fi
sudo bash -c "echo 8096 > /sys/module/nf_conntrack/parameters/hashsize"
sudo sysctl -p
#sudo bash -c "sh set_firewall_rules.sh"
