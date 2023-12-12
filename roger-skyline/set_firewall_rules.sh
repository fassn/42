#!/bin/bash

if grep -q '# Configuration suggested and added from https://javapipe.com/blog/iptables-ddos-protection/' /etc/sysctl.conf; then
	echo Nothing to add in /etc/sysctl.conf
else
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
net.netfilter.nf_conntrack_max = 10000000 
net.netfilter.nf_conntrack_tcp_loose = 0 
net.netfilter.nf_conntrack_tcp_timeout_established = 1800 
net.netfilter.nf_conntrack_tcp_timeout_close = 10 
net.netfilter.nf_conntrack_tcp_timeout_close_wait = 10 
net.netfilter.nf_conntrack_tcp_timeout_fin_wait = 20 
net.netfilter.nf_conntrack_tcp_timeout_last_ack = 20 
net.netfilter.nf_conntrack_tcp_timeout_syn_recv = 20 
net.netfilter.nf_conntrack_tcp_timeout_syn_sent = 20 
net.netfilter.nf_conntrack_tcp_timeout_time_wait = 10 
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
fi

sudo iptables -P INPUT DROP

echo "Adding several rules to prevent basic DOS attacks"
# source: https://javapipe.com/blog/iptables-ddos-protection

### LOG ###
sudo iptables -t mangle -A PREROUTING -p tcp --dport 2222 --syn -j LOG --log-prefix "SSH SYN: "

### 1: Drop invalid packets ### 
# /!\ This blocks connection to SSH if tcp ! --match multiport --dports http,https,2222 not set ! /!\
sudo iptables -t mangle -A PREROUTING -p tcp -m conntrack --ctstate INVALID -j DROP

### 2: Drop TCP packets that are new and are not SYN ### 
sudo iptables -t mangle -A PREROUTING -p tcp ! --syn --match multiport --dports http,https,2222 -m conntrack --ctstate NEW -j DROP

### 3: Drop SYN packets with suspicious MSS value ### 
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 -m conntrack --ctstate NEW -m tcpmss ! --mss 536:65535 -j DROP

### 4: Block packets with bogus TCP flags ### 
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags FIN,SYN,RST,PSH,ACK,URG NONE -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags FIN,SYN FIN,SYN -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags SYN,RST SYN,RST -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags FIN,RST FIN,RST -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags FIN,ACK FIN -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ACK,URG URG -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ACK,FIN FIN -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ACK,PSH PSH -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ALL ALL -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ALL NONE -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ALL FIN,PSH,URG -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ALL SYN,FIN,PSH,URG -j DROP
sudo iptables -t mangle -A PREROUTING -p tcp --match multiport --dports http,https,2222 --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP

### 6: Drop ICMP (you usually don't need this protocol) ###
sudo iptables -t mangle -A PREROUTING -p icmp -j DROP

### 7: Drop fragments in all chains ###
sudo iptables -t mangle -A PREROUTING -f -j DROP

### 8: Limit connections per source IP ###
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 -m connlimit --connlimit-above 111 -j REJECT --reject-with tcp-reset

### 9: Limit RST packets ###
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 --tcp-flags RST RST -m limit --limit 2/s --limit-burst 2 -j ACCEPT
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 --tcp-flags RST RST -j DROP

### 10: Limit new TCP connections per second per source IP ###
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 -m conntrack --ctstate NEW -m limit --limit 60/s --limit-burst 20 -j ACCEPT
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 -m conntrack --ctstate NEW -j DROP

### SSH brute-force protection ###
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 -m conntrack --ctstate NEW -m recent --set
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 -m conntrack --ctstate NEW -m recent --update --seconds 60 --hitcount 10 -j DROP

### Protection against port scanning ###
sudo iptables -N port-scanning
sudo iptables -A port-scanning -p tcp --match multiport --dports http,https,2222 --tcp-flags SYN,ACK,FIN,RST RST -m limit --limit 1/s --limit-burst 2 -j RETURN
sudo iptables -A port-scanning -j DROP

echo "Allowing traffic from http,https,2222 ports and established traffic"
# Allowing SSH connection from LAN
sudo iptables -A INPUT -i lo -j ACCEPT
sudo iptables -A INPUT -p tcp --match multiport --dports http,https,2222 -j ACCEPT
# Allowing Internet traffic
sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

### Make the iptables rules persistent after reboot
sudo bash -c "iptables-save > /etc/iptables/rules.v4"
