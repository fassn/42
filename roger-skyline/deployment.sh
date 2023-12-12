#!/bin/bash

resolv_conf_d_head="/etc/resolvconf/resolv.conf.d/head"
network_interfaces="/etc/network/interfaces"
network_manager_network_manager_conf="/etc/NetworkManager/NetworkManager.conf"
ssh_sshd_config="/etc/ssh/sshd_config"
sysctl_conf="/etc/sysctl.conf"
crontab="/etc/crontab"
cron_d="/etc/cron.d"
var_www_html="/var/www/html"
ssl_certs="/etc/ssl/certs"
ssl_private="/etc/ssl/private"
apache2_sites_available="/etc/apache2/sites-available"
apache2_conf_available="/etc/apache2/conf-available"

function valid_ip()
{
    local  ip=$1
    local  stat=1

    if [[ $ip =~ ^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$ ]]; then
        OIFS=$IFS
        IFS='.'
        ip=($ip)
        IFS=$OIFS
        [[ ${ip[0]} -le 255 && ${ip[1]} -le 255 \
            && ${ip[2]} -le 255 && ${ip[3]} -le 255 ]]
        stat=$?
    fi
    return $stat
}
    read -r -p "Have you run 'bash sudo_install.sh' prior to this script? 
If not Press Ctrl+C now! " input

sudo apt-get update
sudo apt-get -y upgrade
sudo apt-get -y install vim net-tools resolvconf iptables-persistent incron mailutils apache2 gcc make perl linux-headers-amd64 apt-transport-https curl fail2ban

echo "Install Visual Studio Code"
curl -sSL https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
sudo apt update
sudo apt install code

sudo systemctl enable apache2

# Set basic VIM settings
sudo bash -c "echo 'syntax on
set nu
set colorcolumn=80
set tabstop=4
set shiftwidth=4
set cindent' >> /home/$USER/.vimrc"

# Update/Upgrade system and installs needed packages
#sudo bash -c "update_system_and_install_pkg.sh"

if grep -q 'auto enp0s3' /etc/network/interfaces; then
	echo Configuration has already been set
else
    while true
    do
        read -r -p "do you want to set a local static ip? [Y/n] " input

        case $input in
            [yY][eE][sS]|[yY]|"")
        while true
        do
            read -r -p "local static ip address? [x.x.x.x] " ip
            if valid_ip $ip; then
                break
            else
                echo "Invalid input..."
            fi
        done
        while true
        do
            read -r -p "local static submask? [x.x.x.x] " submask
            if valid_ip $submask; then
                break
            else
                echo "Invalid input..."
            fi
        done
        while true
        do
            read -r -p "local static broadcast? [x.x.x.x] " broadcast
            if valid_ip $broadcast; then
                break
            else
                echo "Invalid input..."
            fi
        done
        while true
        do
            read -r -p "local static gateway? [x.x.x.x] " gateway
            if valid_ip $gateway; then
                break
            else
                echo "Invalid input..."
            fi
        done
            read -r -p "dns-domain? ex: 42.fr " dns_domain
            read -r -p "dns-search? ex: 42.fr " dns_search
            read -r -p "dns-nameservers? ex: 10.51.1.42 " dns_nameservers

        echo "Setting up static ip $ip w/ $submask submask"
                sudo bash -c "echo '
# The primary network interface
auto enp0s3
iface enp0s3 inet static
        address $ip
        netmask $submask
        broadcast $broadcast
        gateway $gateway' >> $network_interfaces"
        if [ -n "$dns_domain" ]; then
            sudo bash -c "echo '        dns-domain $dns_domain' >> $network_interfaces"
        fi
        if [ -n "$dns_search" ]; then
            sudo bash -c "echo '        dns-search $dns_search' >> $network_interfaces"
        fi
        if [ -n "$dns_nameservers" ]; then
            sudo bash -c "echo '        dns-nameservers $dns_nameservers' >> $network_interfaces"
        fi
    break
    ;;
        [nN][oO]|[nN])
    break
    ;;
        *)
        echo "Invalid input..."
    ;;
    esac
    done
fi

if grep -q 'rc-manager=unmanaged' $network_manager_network_manager_conf; then
    echo "NetworkManager is already configured properly"
else
    echo "Adding rc-manager=unmanaged to $network_manager_network_manager_conf"
    sudo bash -c "sed -i '/main/a rc-manager=unmanaged' $network_manager_network_manager_conf"
fi


# If a DNS wasn't given by user before
if [ -z "$dns_nameservers" ]; then
    dns_nameservers="192.168.0.254"
fi

if grep -q $dns_nameservers $resolv_conf_d_head; then
    echo "$resolv_conf_d_head is already configured properly"
else
    echo "Adding nameservers to $resolv_conf_d_head"
	if [ -n "$dns_domain" ]; then
            sudo bash -c "echo 'domain $dns_domain' >> $resolv_conf_d_head"
        fi
	if [ -n "$dns_search" ]; then
            sudo bash -c "echo 'search $dns_search' >> $resolv_conf_d_head"
        fi
            sudo bash -c "echo 'nameserver $dns_nameservers' >> $resolv_conf_d_head"
fi

echo Flushing current ip addr
sudo ip addr flush enp0s3

echo Now restarting networking service to apply changes...
sudo systemctl restart networking

# Set fixed ip & related DNS and configuration
#sudo bash -c "set_fixed_ip_42.sh"

if grep -q 'PermitRootLogin no' $ssh_sshd_config; then
    echo Root is already forbidden to login through SSH
else
    while true
    do
        read -r -p "Do you want to forbid root to login through SSH? [Y/n] " input
        case $input in
        [yY][eE][sS]|[yY]|"")
            echo "Adding PermitRootLogin no to $ssh_sshd_config"
            sudo bash -c "sed -i '/#PermitRootLogin/a PermitRootLogin no' $ssh_sshd_config"
        break
    ;;
        [nN][oO]|[nN])
        break
    ;;
        *)
        echo "Invalid input..."
    ;;
    esac
    done
fi

while true
do
    read -r -p "Do you change SSH default port? [Y/n] " input
    case $input in
    [yY][eE][sS]|[yY]|"")
        while true
        do
            read -r -p "New SSH port? " ssh_port
            if (($ssh_port >= 1024 && $ssh_port <= 65535))
            then
                break
            else
                echo Port needs to be in range 1024-65535
            fi
        done
        if grep -q "Port $ssh_port" $ssh_sshd_config; then
            echo "Port $ssh_port is already set"
        else
            echo "Adding Port $ssh_port to $ssh_sshd_config"
            sudo bash -c "sed -i '/#Port 22/a Port $ssh_port' $ssh_sshd_config"
	    sudo /etc/init.d/ssh reload
        fi
    break
;;
    [nN][oO]|[nN])
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

if grep -q 'PasswordAuthentication no' $ssh_sshd_config; then
    echo "SSH key pairs authentication only is already set."
else
    while true
    do
        read -r -p "Do you want to prevent Password Authentication? [Y/n] " input
        case $input in
        [yY][eE][sS]|[yY]|"")
	    read -r -p "Since you want to restrict SSH access to SSH keys, you should take the time NOW to create the keys from your host and send it to this machine. 
Usage: ssh-keygen THEN 
ssh-copy-id -i /.ssh/KEY_rsa -p PORT USER@127.0.0.1" dummy 
            echo "Adding PasswordAuthentication no to $ssh_sshd_config"
            sudo bash -c "sed -i '/#PasswordAuthentication/a PasswordAuthentication no' $ssh_sshd_config"
            echo "You will still need to setup the SSH key pairs manually"
        break
    ;;
        [nN][oO]|[nN])
        break
    ;;
        *)
        echo "Invalid input..."
    ;;
    esac
    done
fi

echo "Now restarting SSH service"
sudo /etc/init.d/ssh reload

# Set SSH to port $ssh_port & prevent password authentication. SSH keys need to be created manually
#sudo bash -c "update_ssh_access.sh"

if grep -q '# Configuration suggested and added from https://javapipe.com/blog/iptables-ddos-protection/' $sysctl_conf; then
    echo "Nothing to add in $sysctl_conf"
else
    while true
    do
        read -r -p "Do you want to add some DOS protection kernel settings (recommended)? [Y/n] " input
        case $input in
        [yY][eE][sS]|[yY]|"")
 	    sudo bash -c "echo '# Configuration suggested and added from https://javapipe.com/blog/iptables-ddos-protection/
kernel.printk = 4 4 1 7 
kernel.panic = 10 
kernel.sysrq = 0 
kernel.shmmax = 4294967296 
kernel.shmall = 4194304 
kernel.core_uses_pid = 1 
kernel.msgmnb = 65536 
kernel.msgmax = 65536 
vm.swappiness = 20 
vm.dirty_ratio = 80 
vm.dirty_background_ratio = 5 
fs.file-max = 2097152 
net.core.netdev_max_backlog = 262144 
net.core.rmem_default = 31457280 
net.core.rmem_max = 67108864 
net.core.wmem_default = 31457280 
net.core.wmem_max = 67108864 
net.core.somaxconn = 65535 
net.core.optmem_max = 25165824 
net.ipv4.neigh.default.gc_thresh1 = 4096 
net.ipv4.neigh.default.gc_thresh2 = 8192 
net.ipv4.neigh.default.gc_thresh3 = 16384 
net.ipv4.neigh.default.gc_interval = 5 
net.ipv4.neigh.default.gc_stale_time = 120 
net.ipv4.tcp_slow_start_after_idle = 0 
net.ipv4.ip_local_port_range = 1024 65535 
net.ipv4.ip_no_pmtu_disc = 1 
net.ipv4.route.flush = 1 
net.ipv4.route.max_size = 8048576 
net.ipv4.icmp_echo_ignore_broadcasts = 1 
net.ipv4.icmp_ignore_bogus_error_responses = 1 
net.ipv4.tcp_congestion_control = htcp 
net.ipv4.tcp_mem = 65536 131072 262144 
net.ipv4.udp_mem = 65536 131072 262144 
net.ipv4.tcp_rmem = 4096 87380 33554432 
net.ipv4.udp_rmem_min = 16384 
net.ipv4.tcp_wmem = 4096 87380 33554432 
net.ipv4.udp_wmem_min = 16384 
net.ipv4.tcp_max_tw_buckets = 1440000 
net.ipv4.tcp_tw_recycle = 0 
net.ipv4.tcp_tw_reuse = 1 
net.ipv4.tcp_max_orphans = 400000 
net.ipv4.tcp_window_scaling = 1 
net.ipv4.tcp_rfc1337 = 1 
net.ipv4.tcp_syncookies = 1 
net.ipv4.tcp_synack_retries = 1 
net.ipv4.tcp_syn_retries = 2 
net.ipv4.tcp_max_syn_backlog = 16384 
net.ipv4.tcp_timestamps = 1 
net.ipv4.tcp_sack = 1 
net.ipv4.tcp_fack = 1 
net.ipv4.tcp_ecn = 2 
net.ipv4.tcp_fin_timeout = 10 
net.ipv4.tcp_keepalive_time = 600 
net.ipv4.tcp_keepalive_intvl = 60 
net.ipv4.tcp_keepalive_probes = 10 
net.ipv4.tcp_no_metrics_save = 1 
net.ipv4.ip_forward = 0 
net.ipv4.conf.all.accept_redirects = 0 
net.ipv4.conf.all.send_redirects = 0 
net.ipv4.conf.all.accept_source_route = 0 
net.ipv4.conf.all.rp_filter = 1' >> /etc/sysctl.conf"
sudo sysctl -p   
        break
    ;;
        [nN][oO]|[nN])
        break
    ;;
        *)
        echo "Invalid input..."
    ;;
    esac
    done
fi

while true
do
    read -r -p "Do you want to add firewall rules w/ iptables? [Y/n] " input
    case $input in
        [yY][eE][sS]|[yY]|"")
            if [ -z "$ssh_port" ]; then
                ssh_port=22
            fi
            echo Adding several rules to prevent basic DOS attacks
            # source: https://javapipe.com/blog/iptables-ddos-protection
            while true
            do
                read -r -p "Drop all INPUT traffic? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    sudo iptables -P INPUT DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Log all SYN traffic from SSH port? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### LOG ###
                    sudo iptables -t mangle -A PREROUTING -p tcp --dport $ssh_port --syn -j LOG --log-prefix "SSH SYN: "
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Drop INVALID packets? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 1: Drop invalid packets ### 
                    sudo iptables -t mangle -A PREROUTING -p tcp -m conntrack --ctstate INVALID -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Drop TCP packets that are new AND not SYN? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 2: Drop TCP packets that are new and are not SYN ### 
                    sudo iptables -t mangle -A PREROUTING -p tcp ! --syn --match multiport --dports http,https,$ssh_port -m conntrack --ctstate NEW -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Drop SYN packets with syspicious MSS value? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 3: Drop SYN packets with suspicious MSS value ### 
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port -m conntrack --ctstate NEW -m tcpmss ! --mss 536:65535 -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Drop packets with bogus TCP flags? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 4: Block packets with bogus TCP flags ### 
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags FIN,SYN,RST,PSH,ACK,URG NONE -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags FIN,SYN FIN,SYN -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags SYN,RST SYN,RST -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags FIN,RST FIN,RST -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags FIN,ACK FIN -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ACK,URG URG -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ACK,FIN FIN -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ACK,PSH PSH -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ALL ALL -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ALL NONE -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ALL FIN,PSH,URG -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ALL SYN,FIN,PSH,URG -j DROP
                    sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Drop ICMP (This will block the ping command!)? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 6: Drop ICMP (you usually don't need this protocol) ###
                    sudo iptables -t mangle -A PREROUTING -p icmp -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Drop fragments in all chains? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 7: Drop fragments in all chains ###
                    sudo iptables -t mangle -A PREROUTING -f -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Limit connections per source IP? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 8: Limit connections per source IP ###
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port -m connlimit --connlimit-above 111 -j REJECT --reject-with tcp-reset
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Limit RST packets? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 9: Limit RST packets ###
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags RST RST -m limit --limit 2/s --limit-burst 2 -j ACCEPT
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags RST RST -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Limit new TCP connections per second per source IP? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### 10: Limit new TCP connections per second per source IP ###
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port -m conntrack --ctstate NEW -m limit --limit 60/s --limit-burst 20 -j ACCEPT
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port -m conntrack --ctstate NEW -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Setup brute-force protection? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### brute-force protection ###
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port -m conntrack --ctstate NEW -m recent --set
                    sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port -m conntrack --ctstate NEW -m recent --update --seconds 60 --hitcount 10 -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            while true
            do
                read -r -p "Setup protection against port scanning? [Y/n] " input
                case $input in
                    [yY][eE][sS]|[yY]|"")
                    ### Protection against port scanning ###
                    sudo iptables -N port-scanning
                    sudo iptables -A port-scanning -p tcp --match multiport --dports http,https,$ssh_port --tcp-flags SYN,ACK,FIN,RST RST -m limit --limit 1/s --limit-burst 2 -j RETURN
                    sudo iptables -A port-scanning -j DROP
                break
                ;;
                    [nN][oO]|[nN])
                break
                ;;
                    *)
                    echo "Invalid input..."
                ;;
                esac
            done
            echo "Allowing traffic from http,https,$ssh_port ports and established traffic"
            # Allowing SSH connection from LAN
            sudo iptables -A INPUT -i lo -j ACCEPT
            sudo iptables -A INPUT -p tcp --match multiport --dports http,https,$ssh_port -j ACCEPT
            # Allowing Internet traffic
            sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
            ### Make the iptables rules persistent after reboot
            sudo bash -c "iptables-save > /etc/iptables/rules.v4"
    break
    ;;
        [nN][oO]|[nN])
    break
    ;;
        *)
        echo "Invalid input..."
    ;;
    esac
done

# Set iptables to block traffic besides port 2222 & some basic DOS protection
#sudo bash -c "set_firewall_rules.sh"

while true
do
    read -r -p "Disable Advanced Linux Sound Architecture Daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
    # Disables Advanced Linux Sound Architecture
    sudo systemctl --now disable alsa-utils
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable bluetooth daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables bluetooth
        sudo systemctl --now disable bluetooth
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable HDD temp daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables HDD temp
        sudo systemctl --now disable hddtemp
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable HWclock daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables HWclock
        sudo systemctl --now disable hwclock
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable lm sensors daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables lm-sensors
        sudo systemctl --now disable lm-sensors
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable rsync daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables rsync
        sudo systemctl --now disable rsync
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable saned daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables saned
        sudo systemctl --now disable saned
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Disable Speech Dispatcher daemon? [y/N] " input
    case $input in
    [yY][eE][sS]|[yY])
        # Disables speech-dispatcher
        sudo systemctl --now disable speech-dispatcher
    break
;;
    [nN][oO]|[nN]|"")
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

# Disable unnecessary daemons
#sudo bash -c "disable_unnecessary_services.sh"

while true
do
    read -r -p "Add Update/Upgrade script to run at every reboot AND every monday at 4 a.m.? [Y/n] " input
    case $input in
    [yY][eE][sS]|[yY]|"")
        # Adds update/upgrade script to run @ every reboot & every monday @ 4 a.m.
        echo "Copy update_script.sh to $cron_d"
        sudo bash -c "cp update_script.sh $cron_d/."
        if grep -q '0 4\t* * 1\troot\tsh $cron_d/update_script.sh\n@reboot\t\troot\tsh $cron_d/update_script.sh' $crontab
        then
            echo "$crontab is already set for this script"
        else
            sudo bash -c "echo -e '0 4\t* * 1\troot\tsh $cron_d/update_script.sh\n@reboot\t\troot\tsh $cron_d/update_script.sh' >> $crontab"
        fi
    break
;;
    [nN][oO]|[nN])
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

while true
do
    read -r -p "Monitor $crontab file and send email to root if change occurs? [Y/n] " input
    case $input in
    [yY][eE][sS]|[yY]|"")
        # Monitors $crontab and sends an email to root if a change occurs
        echo $USER | sudo tee -a /etc/incron.allow
        echo "Copy monitor_crontab.sh to $cron_d"
        sudo bash -c "cp monitor_crontab.sh $cron_d/."
        sudo bash -c "echo -e '/etc/crontab IN_MODIFY $cron_d/monitor_crontab.sh' >> /etc/incron.d/monitor_crontab"
        sudo service incron restart
    break
;;
    [nN][oO]|[nN])
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done

# Deploys Apache server
#sudo bash -c "apache_deployment.sh"

# Checks if Apache2 is running
if ps -ef | grep -q apache2
then
	echo 'Apache2 service is already running'
else
	sudo systemctl start apache2
fi

# Generate SSL self-signed certificate & key
if [ ! -f $ssl_private/apache-selfsigned.key ]; then
    sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout $ssl_private/apache-selfsigned.key -out $ssl_certs/apache-selfsigned.crt
fi

# Generate a strong Diffie-Hellman group
if [ ! -f $ssl_certs/dhparam.pem ]; then
    sudo openssl dhparam -out $ssl_certs/dhparam.pem 2048
fi

while true
do
read -r -p "Would you like to create a folder for your website?
(And set up Apache for SSL self-signed certificate in a Virtual Host [Y/n] " input
    case $input in
    [yY][eE][sS]|[yY]|"")
    read -r -p "Folder name to be created in $var_www_html? " domain
    sudo bash -c "mkdir -p $var_www_html/$domain"
    echo "Create a simple template page within $var_www_html/$domain"
    sudo bash -c "echo '<html>
  <body>
    <center><h1>This is my website!</h1></center>
  </body>
</html>' >> $var_www_html/$domain/index.html"
    sudo cat $var_www_html/$domain/index.html
    
    # Changes ownership of /var/www/html to www-data
    sudo chown -R www-data: $var_www_html

    read -r -p "From which port would you like to access the webserver?
If you add a port forwarding rule, you'll be able to access to the webserver from that port. (ex: localhost:8080 ==> $ip:80? " apache_proxy_port

    # If a static IP wasn't set before, pick current local IP address
    if [ -z "$ip" ]; then
	ip=`sudo ifconfig enp0s3 | grep "inet " | cut -d ' ' -f10`
    fi

    # Creates a Virtual Host File for our website
    sudo bash -c "echo -e '<VirtualHost *:80>
	ServerName $ip
	ServerAdmin admin@$domain

	ProxyPreserveHost On
	ProxyRequests Off
	SSLProxyEngine On
	ProxyPass / ! 
	ProxyPass / \x22http://localhost:$apache_proxy_port\x22
	ProxyPassReverse / \x22http://localhost:$apache_proxy_port\x22

	Redirect Permanent / \x22https://$ip/\x22
</VirtualHost>

<VirtualHost *:443>
	ServerName $ip
	ServerAdmin admin@$domain
	DocumentRoot /var/www/html/$domain

	SSLEngine On
	SSLCertificateFile $ssl_certs/apache-selfsigned.crt
	SSLCertificateKeyFile $ssl_private/apache-selfsigned.key

	ErrorLog /${domain}_error.log
</VirtualHost>' >> $apache2_sites_available/$domain.conf"

    # Create the SSL params file
    sudo bash -c "echo -e '# from https://cipherli.st/
    # and https://raymii.org/s/tutorials/Strong_SSL_Security_On_Apache2.html

    SSLCipherSuite EECDH+AESGCM:EDH+AESGCM:AES256+EECDH:AES256+EDH
    SSLProtocol All -SSLv2 -SSLv3
    SSLHonorCipherOrder On
    # Disable preloading HSTS for now.  You can use the commented out header line that includes
    # the \x22preload\x22 directive if you understand the implications.
    #Header always set Strict-Transport-Security \x22max-age=63072000; includeSubdomains; preload\x22
    Header always set Strict-Transport-Security \x22max-age=63072000; includeSubdomains\x22
    Header always set X-Frame-Options DENY
    Header always set X-Content-Type-Options nosniff
    # Requires Apache >= 2.4
    SSLCompression off 
    SSLSessionTickets Off
    SSLUseStapling on 
    SSLStaplingCache \x22shmcb:logs/stapling-cache(150000)\x22

    SSLOpenSSLConfCmd DHParameters \x22/etc/ssl/certs/dhparam.pem\x22' >> $apache2_conf_available/ssl-params.conf"

    # Make a backup of the default-SSL conf
    sudo cp $apache2_sites_available/default-ssl.conf $apache2_sites_available/default-ssl.conf.bak

    # Replace default-SSL conf
    sudo bash -c "echo -e '<IfModule mod_ssl.c>
        <VirtualHost _default_:443>
                ServerAdmin your_email@example.com
                ServerName server_domain_or_IP

                DocumentRoot /var/www/html

                ErrorLog ${APACHE_LOG_DIR}/error.log
                CustomLog ${APACHE_LOG_DIR}/access.log combined

                SSLEngine on

                SSLCertificateFile      $ssl_certs/apache-selfsigned.crt
                SSLCertificateKeyFile $ssl_private/apache-selfsigned.key

                <FilesMatch \x22\.(cgi|shtml|phtml|php)$\x22>
                                SSLOptions +StdEnvVars
                </FilesMatch>
                <Directory /usr/lib/cgi-bin>
                                SSLOptions +StdEnvVars
                </Directory>

                BrowserMatch \x22MSIE [2-6]\x22 \
                               nokeepalive ssl-unclean-shutdown \
                               downgrade-1.0 force-response-1.0
        </VirtualHost>
</IfModule>' > $apache2_sites_available/default-ssl.conf"

    # Enable ssl, headers, proxy, proxy_http mods
    sudo a2enmod ssl
    sudo a2enmod headers
    sudo a2enmod proxy
    sudo a2enmod proxy_http

    # Enable SSL Virtual Host
    sudo a2ensite default-ssl

    # Enables the Virtual Host
    sudo a2ensite $domain.conf

    # Enable ssl-params conf
    sudo a2enconf ssl-params

    # Restart Apache service
    sudo systemctl restart apache2

    echo "Don't forget to add HTTP port forwarding in VirtualBox.
    ex: Host: 127.0.0.1:$apache_proxy_port Guest: ip:80"
    break
;;
    [nN][oO]|[nN])
    break
;;
    *)
    echo "Invalid input..."
;;
esac
done
