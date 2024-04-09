#!/bin/sh

if [ $# -lt 4 ]
then
    echo -e "usage: ./lxc_creat.sh mode rootbox_dir lxc_name"
    echo -e "        for example: ./lxc_create_lxc3.sh DEBUG /home/user/HiSTBLinuxV100R002/out/hi3716mv410/hi3716m41dma_ca_debug/rootbox stb arm-histbv300-linux"
    exit 1
fi
lxc_enable_net="yes"
if [ ! -z "$5" ] && test "X$5" = "Xno"; then
lxc_enable_net="no"
fi

LXC_MODE=$1
SDK_PATH=$2/../../../..
PREFIX=$2
name=$3
toolchain_name=$4

SAMPLE_OUT_PATH=$2/../$OBJ_NAME/sample

SOCKET_SERVER_ADDR=10.67.212.63
SOCKET_TEST_PORT=4444

# create fs directory tree
install_fs_dir()
{
    tree="\
$PREFIX/$lxc_rootfs_dir/dev \
$PREFIX/$lxc_rootfs_dir/home \
$PREFIX/$lxc_rootfs_dir/root \
$PREFIX/$lxc_rootfs_dir/etc \
$PREFIX/$lxc_rootfs_dir/etc/init.d \
$PREFIX/$lxc_rootfs_dir/bin \
$PREFIX/$lxc_rootfs_dir/sbin \
$PREFIX/$lxc_rootfs_dir/proc \
$PREFIX/$lxc_rootfs_dir/sys \
$PREFIX/$lxc_rootfs_dir/mnt \
$PREFIX/$lxc_rootfs_dir/tmp \
$PREFIX/$lxc_rootfs_dir/dev/pts \
$PREFIX/$lxc_rootfs_dir/lib \
$PREFIX/$lxc_rootfs_dir/lib64 \
$PREFIX/$lxc_rootfs_dir/usr/sbin \
$PREFIX/$lxc_rootfs_dir/usr/lib \
$PREFIX/$lxc_rootfs_dir/usr/lib64"

    mkdir -p $tree
        chmod 755 $tree

    mkdir -p $PREFIX/`dirname $lxc_config_file`
}

# create container init script for CA debug
install_dbg_fs_scripts()
{
    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/inittab
::sysinit:/etc/init.d/rcS
tty1::respawn:/bin/sh
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/inittab

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS
#!/bin/sh
/etc/firewall
EOF
    chmod 744 $PREFIX/$lxc_rootfs_dir//etc/init.d/rcS

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/passwd
root:x:0:0:root:/root:/bin/sh
stb:x:1000:1000:Linux User,,,:/home:/bin/sh
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/passwd

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/group
root:x:0:root
gstb:x:1000:
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/group

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/shadow
$name:\$1\$eF8I65UL\$7FfdLFZEBw46GPpAOYcOQ/:0:0:99999:7:::
EOF
    chmod 640 $PREFIX/$lxc_rootfs_dir/etc/shadow

    # udhcpc scripts
    mkdir -p $PREFIX/$lxc_rootfs_dir/usr/share/udhcpc
    cp -r $PREFIX/usr/share/udhcpc/* $PREFIX/$lxc_rootfs_dir/usr/share/udhcpc
    cat <<EOF >>$PREFIX/$lxc_rootfs_dir/usr/share/udhcpc/default.bound
## Allow response packet from ouside come in
iptables -A INPUT -i \$interface -p tcp -m tcp --sport $SOCKET_TEST_PORT -d \$ip/32 -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables -nL --line-number
EOF
    cat <<EOF >>$PREFIX/$lxc_rootfs_dir/usr/share/udhcpc/default.renew
## Allow response packet from ouside come in
/etc/firewall
iptables -A INPUT -i \$interface -p tcp -m tcp --sport $SOCKET_TEST_PORT -d \$ip/32 -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables -nL --line-number
EOF
    cat <<EOF >>$PREFIX/$lxc_rootfs_dir/usr/share/udhcpc/default.leasefail
echo "Lease failed, try again..."
EOF
}


# create container init script for CA release
install_rel_fs_scripts()
{
    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/inittab
::sysinit:/etc/init.d/rcS
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/inittab

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS
#!/bin/sh
/etc/firewall
EOF
    chmod 744 $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/passwd
root:x:0:0:root:/root:/bin/false
stb:x:1000:1000:Linux User,,,:/home:/bin/sh
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/passwd

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/group
root:x:0:root
gstb:x:1000:
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/group

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/shadow
root:!:15506:0:99999:7:::
EOF
    chmod 640 $PREFIX/$lxc_rootfs_dir/etc/shadow

    # udhcpc scripts
    mkdir -p $PREFIX/$lxc_rootfs_dir/usr/share/udhcpc
    cp -r $PREFIX/usr/share/udhcpc/* $PREFIX/$lxc_rootfs_dir/usr/share/udhcpc

    cat <<EOF >>$PREFIX/$lxc_rootfs_dir/usr/share/udhcpc/default.bound
## Allow response packet from ouside come in
iptables -A INPUT -i \$interface -p tcp -m tcp --sport $SOCKET_TEST_PORT -d \$ip/32 -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
EOF
    cat <<EOF >>$PREFIX/$lxc_rootfs_dir/usr/share/udhcpc/default.renew
## Allow response packet from ouside come in
/etc/firewall
iptables -A INPUT -i \$interface -p tcp -m tcp --sport $SOCKET_TEST_PORT -d \$ip/32 -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
EOF
}

# install busybox
install_busybox()
{
    # refer to Busybox Config File For LXC
    cp -r $PREFIX/home/stb/* $PREFIX/$lxc_rootfs_dir/
    cp -r $PREFIX/usr/sbin/init.lxc $PREFIX/$lxc_rootfs_dir/usr/sbin/
    cp -r $PREFIX/sbin/iptables $PREFIX/$lxc_rootfs_dir/sbin/
    cp -r $PREFIX/sbin/xtables-multi $PREFIX/$lxc_rootfs_dir/sbin/
    cp -r $PREFIX/lib/libnss_compat* $PREFIX/$lxc_rootfs_dir/lib/
    cp -r $PREFIX/lib/libnss_files* $PREFIX/$lxc_rootfs_dir/lib/
    cp -r $PREFIX/usr/sbin/mount.exfat $PREFIX/$lxc_rootfs_dir/usr/sbin/
}


install_app()
{
    make -C $SDK_PATH/sample/lxc_ipc
    cp -fr $SAMPLE_OUT_PATH/lxc_ipc/launch_app      $PREFIX/$lxc_rootfs_dir/home/
    $STRIP $PREFIX/$lxc_rootfs_dir/home/launch_app
    cp -f $SAMPLE_OUT_PATH/lxc_ipc/ipc_client_test      $PREFIX/$lxc_rootfs_dir/home/ && \
    $STRIP $PREFIX/$lxc_rootfs_dir/home/ipc_client_test
    cp -f $SAMPLE_OUT_PATH/lxc_ipc/socket_client      $PREFIX/$lxc_rootfs_dir/home/ && \
    $STRIP $PREFIX/$lxc_rootfs_dir/home/socket_client

    cat << EOF > $PREFIX/$lxc_rootfs_dir/home/lxc0_start.sh
#!/bin/sh

/etc/firewall

udhcpc -i eth0

## Allow packet from browse to outside
iptables -A OUTPUT -o eth0 -p tcp -m tcp --dport $SOCKET_TEST_PORT -d $SOCKET_SERVER_ADDR/32 -m conntrack --ctstate NEW,ESTABLISHED,RELATED -j ACCEPT

echo "----------------Firewall Config---------------"
iptables -L
echo "----------------------------------------------"

echo "Start DVB alient app..."
/home/ipc_client_test &

echo "Start socket client app..."
/home/socket_client $SOCKET_SERVER_ADDR
EOF
    chmod ug+x $PREFIX/$lxc_rootfs_dir/home/lxc0_start.sh
}
##########################Generate firewall for LXC#####################################
install_firewall()
{
    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/firewall
#!/bin/sh


echo 0 > /proc/sys/net/ipv4/ip_forward

##Set default policy to DROP
iptables -P INPUT DROP
iptables -P OUTPUT DROP
iptables -P FORWARD DROP

## Flush, Zero all chains
iptables -F
iptables -t raw -F
iptables -t nat -F

iptables -Z
iptables -t raw -Z
iptables -t nat -Z

## Delete any user defined chains
iptables -X
iptables -t raw -X
iptables -t nat -X

#######################################Define our chain###########################################################
iptables -t raw -N CHECK_TCPFLAGS
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags SYN,RST SYN,RST -j DROP
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags SYN,FIN SYN,FIN -j DROP
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags ALL ALL -j DROP
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags ALL NONE -j DROP
iptables -t raw -A CHECK_TCPFLAGS -p tcp --tcp-flags URG,FIN URG,FIN -j DROP

#######################################PREROUTING chain of raw talbe###########################################################
iptables -t raw -A PREROUTING -f -j DROP
iptables -t raw -A PREROUTING -m addrtype --src-type BLACKHOLE,UNREACHABLE,PROHIBIT,ANYCAST,BROADCAST,MULTICAST -j DROP
iptables -t raw -A PREROUTING -m addrtype --dst-type BLACKHOLE,UNREACHABLE,PROHIBIT,ANYCAST,BROADCAST,MULTICAST -j DROP

#iptables -t raw -A PREROUTING -p icmp -j DROP
#Refuse the echo-request(8/0) from external device. This means external device does not ping our stb
iptables -t raw -A PREROUTING -i eth0 -p icmp --icmp-type echo-request -j DROP

iptables -t raw -A PREROUTING -i eth0 -m addrtype --src-type LOCAL -j DROP

## Reject the connect from outside
iptables -t raw -A PREROUTING -i eth0 -p tcp --tcp-flags ALL SYN -j DROP

iptables -t raw -A PREROUTING -p tcp -j CHECK_TCPFLAGS

iptables -t raw -A PREROUTING -i eth0 -s 127.0.0.1/8 -j DROP

######################################Process INPUT packet########################################
## Allow loop back packet come in
iptables -A INPUT -m conntrack --ctstate INVALID -j DROP

## Allow loop back packet come in
iptables -A INPUT -i lo -j ACCEPT

#Furtive port scanner protection:
iptables -A INPUT -i eth0 -p tcp --tcp-flags SYN,ACK,FIN,RST RST -m limit --limit 1/s --limit-burst 5 -j ACCEPT
iptables -A INPUT -i eth0 -p tcp --tcp-flags SYN,ACK,FIN,RST RST -j DROP

iptables -A INPUT -i eth0 -p icmp -m limit --limit 1/s --limit-burst 10 -j ACCEPT
iptables -A INPUT -i eth0 -p icmp -j DROP

iptables -A INPUT -p icmp --icmp-type echo-reply -j ACCEPT
#We only accept part of icmp type 3
iptables -A INPUT -p icmp --icmp-type 3/0 -j ACCEPT
iptables -A INPUT -p icmp --icmp-type 3/1 -j ACCEPT
iptables -A INPUT -p icmp --icmp-type 3/2 -j ACCEPT
iptables -A INPUT -p icmp --icmp-type 3/3 -j ACCEPT
iptables -A INPUT -p icmp --icmp-type 3/4 -j ACCEPT

#Allow DHCP package come in
iptables -A INPUT -i eth0 -p udp -m udp --sport 67 -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

#Allow eth1 package to communicate with lxc1
iptables -A INPUT -i eth1 -p tcp -s 192.168.1.2/32 -j ACCEPT

######################################Process OUTPUT packet########################################
iptables -t raw -A OUTPUT -f -j DROP
iptables -t raw -A OUTPUT -m addrtype --src-type BLACKHOLE,UNREACHABLE,PROHIBIT,ANYCAST,BROADCAST,MULTICAST -j DROP
iptables -t raw -A OUTPUT -m addrtype --dst-type BLACKHOLE,UNREACHABLE,PROHIBIT,ANYCAST,BROADCAST,MULTICAST -j DROP
#iptables -t raw -A OUTPUT -p icmp -j DROP
iptables -t raw -A OUTPUT -o eth0 -m addrtype --dst-type LOCAL -j DROP

iptables -t raw -A OUTPUT -p tcp -j CHECK_TCPFLAGS
## Reject invalid state packet output
iptables -A OUTPUT -m conntrack --ctstate INVALID -j DROP

iptables -A OUTPUT -o eth0 -d 127.0.0.1/8 -j DROP

## Allow loop back packet out
iptables -A OUTPUT -o lo -j ACCEPT

#Not send the echo reply(0/0) to outside device. This means external device does not ping our stb
iptables -A OUTPUT -o eth0 -p icmp --icmp-type echo-reply -j DROP

## Allow our STB send echo-request(8/0) to outside.
iptables -A OUTPUT -o eth0 -p icmp --icmp-type echo-request -j ACCEPT

#Allow DHCP package go out
iptables -A OUTPUT -o eth0 -p udp -m udp --dport 67 -m conntrack --ctstate NEW,ESTABLISHED,RELATED -j ACCEPT

#Allow eth1 package to communicate with lxc1
iptables -A OUTPUT -o eth1 -p tcp -d 192.168.1.2/32 -j ACCEPT
EOF
}

# create and deploy lxc config file for CA debug
install_lxc_dbg_config()
{
    cat <<EOF > $PREFIX/$lxc_config_file
lxc.utsname = $name

#lxc.id_map = u 0 1000 10
#lxc.id_map = g 0 1000 10

lxc.cap.keep = net_raw net_admin setuid setgid sys_time

lxc.tty = 1
lxc.pts = 1
lxc.rootfs = $lxc_rootfs_dir
lxc.mount = $lxc_config_dir/fstab
lxc.pivotdir = /tmp/lxc_putold

lxc.mount.entry = /sys/power/state sys/power/state none rw,bind 0 0
lxc.mount.entry = shm dev/shm tmpfs rw,nosuid,nodev,noexec,mode=0660,create=dir 0 0
lxc.mount.entry = /dev/shm dev/shm none rw,bind 0 0

lxc.mount.entry = /dev/hi_adec dev/hi_adec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_adsp dev/hi_adsp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_aenc dev/hi_aenc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ao dev/hi_ao none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ca dev/hi_ca none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_cipher dev/hi_cipher none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_demux dev/hi_demux none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_disp dev/hi_disp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_gpio dev/hi_gpio none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_hdmi dev/hi_hdmi none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_i2c dev/hi_i2c none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ir dev/hi_ir none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_keyled dev/hi_keyled none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_log dev/hi_log none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_mce dev/hi_mce none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_module dev/hi_module none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_otp dev/hi_otp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pm dev/hi_pm none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_png dev/hi_png none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pq dev/hi_pq none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pvr dev/hi_pvr none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sci dev/hi_sci none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_stat dev/hi_stat none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sync dev/hi_sync none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sys dev/hi_sys none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tde dev/hi_tde none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tuner dev/hi_tuner none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_userproc dev/hi_userproc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vdec dev/hi_vdec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vo dev/hi_vo none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vpss dev/hi_vpss none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb0 dev/fb0 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb1 dev/fb1 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb2 dev/fb2 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/jpeg dev/jpeg none bind,optional,create=file 0 0

lxc.mount.entry = /dev/tc_ns_client dev/tc_ns_client none bind,optional,create=file 0 0

lxc.mount.entry = /dev/mmz_userdev dev/mmz_userdev none bind,optional,create=file 0 0
lxc.mount.entry = /dev/mem dev/mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/null dev/null none bind,optional,create=file 0 0
lxc.mount.entry = /dev/urandom dev/urandom none bind,optional,create=file 0 0
lxc.mount.entry = /dev/watchdog dev/watchdog none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fuse dev/fuse none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda  dev/sda  none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda1 dev/sda1 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda2 dev/sda2 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda3 dev/sda3 none bind,optional,create=file 0 0

EOF
if [ "X${lxc_enable_net}" = "Xyes" ]; then
    cat <<EOF >> $PREFIX/$lxc_config_file
#config physical eth0
lxc.network.type = phys
lxc.network.flags = up
lxc.network.link = eth0
lxc.network.name = eth0
lxc.network.ipv4 = 192.168.2.1/24

#config virtual eth1
lxc.network.type = veth
lxc.network.flags = up
lxc.network.link = br1
lxc.network.hwaddr = 4a:49:43:49:79:bf
lxc.network.ipv4 = 192.168.1.3/24
lxc.network.name = eth1
# lxc.network.hwaddr = 4a:4c:4a:fe:79:bc

EOF
fi

    cat <<EOF >> $PREFIX/$lxc_config_file
#config devcies access
lxc.cgroup.devices.deny = a

# /dev/null and zero
lxc.cgroup.devices.allow = c 1:3 rwm
lxc.cgroup.devices.allow = c 1:5 rwm
# consoles
lxc.cgroup.devices.allow = c 5:1 rwm
lxc.cgroup.devices.allow = c 5:0 rwm
lxc.cgroup.devices.allow = c 4:0 rwm
lxc.cgroup.devices.allow = c 4:1 rwm
# /dev/{,u}random
lxc.cgroup.devices.allow = c 1:9 rwm
lxc.cgroup.devices.allow = c 1:8 rwm
lxc.cgroup.devices.allow = c 136:* rwm
lxc.cgroup.devices.allow = c 5:2 rwm
# hi_*
lxc.cgroup.devices.allow = c 218:* rwm
# fb8
lxc.cgroup.devices.allow = c 29:* rwm
# others
lxc.cgroup.devices.allow = c 10:* rwm

lxc.cgroup.devices.allow = b 31:* rwm
lxc.cgroup.devices.allow = c 90:* rwm

lxc.cgroup.devices.allow = b 8:* rwm
EOF

    chmod 644 $PREFIX/usr/var/lib/lxc/$name/config

    cat <<EOF > $PREFIX/$lxc_config_dir/fstab
proc            /home/$name/proc           proc    defaults        0       0
sysfs           /home/$name/sys            sysfs   defaults        0       0
tmp             /home/$name/tmp            tmpfs   nosuid,noexec,nodev,uid=1000,gid=1000,mode=1770        0       0
dev             /home/$name/dev            tmpfs   nosuid,noexec,nodev,gid=1000,mode=0770        0       0
EOF
    chmod 644 $PREFIX/$lxc_config_dir/fstab

}

# create and deploy lxc config file for CA release
install_lxc_rel_config()
{
    cat <<EOF > $PREFIX/$lxc_config_file
lxc.utsname = $name

#lxc.id_map = u 0 1000 10
#lxc.id_map = g 0 1000 10

lxc.cap.keep = net_raw net_admin setuid setgid sys_time
lxc.console = none

lxc.rootfs = $lxc_rootfs_dir
lxc.mount = $lxc_config_dir/fstab
lxc.pivotdir = /tmp/lxc_putold

lxc.mount.entry = /sys/power/state sys/power/state none rw,bind 0 0
lxc.mount.entry = shm dev/shm tmpfs rw,nosuid,nodev,noexec,mode=0660,create=dir 0 0
lxc.mount.entry = /dev/shm dev/shm none rw,bind 0 0

lxc.mount.entry = /dev/hi_adec dev/hi_adec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_adsp dev/hi_adsp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_aenc dev/hi_aenc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ao dev/hi_ao none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ca dev/hi_ca none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_cipher dev/hi_cipher none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_demux dev/hi_demux none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_disp dev/hi_disp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_gpio dev/hi_gpio none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_hdmi dev/hi_hdmi none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_i2c dev/hi_i2c none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_ir dev/hi_ir none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_keyled dev/hi_keyled none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_log dev/hi_log none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_mce dev/hi_mce none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_module dev/hi_module none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_otp dev/hi_otp none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pm dev/hi_pm none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_png dev/hi_png none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pq dev/hi_pq none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_pvr dev/hi_pvr none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sci dev/hi_sci none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_stat dev/hi_stat none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sync dev/hi_sync none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_sys dev/hi_sys none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tde dev/hi_tde none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_tuner dev/hi_tuner none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_userproc dev/hi_userproc none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vdec dev/hi_vdec none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vo dev/hi_vo none bind,optional,create=file 0 0
lxc.mount.entry = /dev/hi_vpss dev/hi_vpss none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb0 dev/fb0 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb1 dev/fb1 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fb2 dev/fb2 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/jpeg dev/jpeg none bind,optional,create=file 0 0

lxc.mount.entry = /dev/tc_ns_client dev/tc_ns_client none bind,optional,create=file 0 0

lxc.mount.entry = /dev/mmz_userdev dev/mmz_userdev none bind,optional,create=file 0 0
lxc.mount.entry = /dev/mem dev/mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/null dev/null none bind,optional,create=file 0 0
lxc.mount.entry = /dev/urandom dev/urandom none bind,optional,create=file 0 0
lxc.mount.entry = /dev/watchdog dev/watchdog none bind,optional,create=file 0 0
lxc.mount.entry = /dev/fuse dev/fuse none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda1 dev/sda1 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda2 dev/sda2 none bind,optional,create=file 0 0
lxc.mount.entry = /dev/sda3 dev/sda3 none bind,optional,create=file 0 0

EOF
if [ "X${lxc_enable_net}" = "Xyes" ]; then
    cat <<EOF >> $PREFIX/$lxc_config_file
#config physical eth0
lxc.network.type = phys
lxc.network.flags = up
lxc.network.link = eth0
lxc.network.name = eth0
lxc.network.ipv4 = 192.168.2.1/24

#config virtual eth1
lxc.network.type = veth
lxc.network.flags = up
lxc.network.link = br1
lxc.network.hwaddr = 4a:49:43:49:79:bf
lxc.network.ipv4 = 192.168.1.3/24
lxc.network.name = eth1
# lxc.network.hwaddr = 4a:4c:4a:fe:79:bc

EOF
fi

    cat <<EOF >> $PREFIX/$lxc_config_file
#config devcies access
lxc.cgroup.devices.deny = a

# /dev/null and zero
lxc.cgroup.devices.allow = c 1:3 rwm
lxc.cgroup.devices.allow = c 1:5 rwm
# consoles
lxc.cgroup.devices.allow = c 5:1 rwm
lxc.cgroup.devices.allow = c 5:0 rwm
lxc.cgroup.devices.allow = c 4:0 rwm
lxc.cgroup.devices.allow = c 4:1 rwm
# /dev/{,u}random
lxc.cgroup.devices.allow = c 1:9 rwm
lxc.cgroup.devices.allow = c 1:8 rwm
lxc.cgroup.devices.allow = c 136:* rwm
lxc.cgroup.devices.allow = c 5:2 rwm
# hi_*
lxc.cgroup.devices.allow = c 218:* rwm
# fb8
lxc.cgroup.devices.allow = c 29:* rwm
# others
lxc.cgroup.devices.allow = c 10:* rwm

lxc.cgroup.devices.allow = b 31:* rwm
lxc.cgroup.devices.allow = c 90:* rwm

lxc.cgroup.devices.allow = b 8:* rwm
EOF

    chmod 644 $PREFIX/usr/var/lib/lxc/$name/config

    cat <<EOF > $PREFIX/$lxc_config_dir/fstab
proc            /home/$name/proc           proc    defaults        0       0
sysfs           /home/$name/sys            sysfs   defaults        0       0
tmp             /home/$name/tmp            tmpfs   nosuid,noexec,nodev,uid=1000,gid=1000,mode=1770        0       0
dev             /home/$name/dev            tmpfs   nosuid,noexec,nodev,gid=1000,mode=0770        0       0
EOF
    chmod 644 $PREFIX/$lxc_config_dir/fstab

}

##################################################################################
delete_files()
{
    file_to_del+=" $PREFIX/$lxc_rootfs_dir/usr/lib/higo-adp/ "
    file_to_del+=" $PREFIX/$lxc_rootfs_dir/usr/lib/libcrypto* "
    file_to_del+=" $PREFIX/$lxc_rootfs_dir/usr/lib/libfreetype* "
    file_to_del+=" $PREFIX/$lxc_rootfs_dir/usr/lib/libHA* "
    file_to_del+=" $PREFIX/$lxc_rootfs_dir/usr/lib/libhigo* "
    file_to_del+=" $PREFIX/$lxc_rootfs_dir/usr/lib/libz* "

    for ff in $file_to_del ; do
        rm  -rf $ff
    done
}
##################################################################################

lxc_config_dir=/usr/var/lib/lxc/$name
lxc_config_file=$lxc_config_dir/config
lxc_rootfs_dir=/home/$name

install_fs_dir
install_busybox
install_firewall
install_app

if [ $LXC_MODE == "DEBUG" ]; then
    install_dbg_fs_scripts
    install_lxc_dbg_config
else
    install_rel_fs_scripts
    install_lxc_rel_config
fi

