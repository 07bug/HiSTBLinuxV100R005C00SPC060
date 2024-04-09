#!/bin/sh

if [ $# -lt 4 ]
then
    echo -e "usage: ./lxc_creat.sh mode rootbox_dir lxc_name"
    echo -e "        for example: ./lxc_create_lxc0.sh DEBUG /home/user/HiSTBLinuxV100R002/out/hi3716mv410/hi3716m41dma_ca_debug/rootbox stb arm-histbv300-linux"
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
$PREFIX/$lxc_rootfs_dir/usr/sbin \
$PREFIX/$lxc_rootfs_dir/usr/lib"

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
EOF
    chmod 744 $PREFIX/$lxc_rootfs_dir//etc/init.d/rcS

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/passwd
root:x:0:0:root:/root:/bin/sh
stb:1000:1000:Linux User,,,:/home:/bin/sh
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
EOF
    chmod 744 $PREFIX/$lxc_rootfs_dir/etc/init.d/rcS

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/passwd
root:x:0:0:root:/root:/bin/false
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/passwd

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/group
root:x:0:root
EOF
    chmod 644 $PREFIX/$lxc_rootfs_dir/etc/group

    cat <<EOF > $PREFIX/$lxc_rootfs_dir/etc/shadow
root:!:15506:0:99999:7:::
EOF
    chmod 640 $PREFIX/$lxc_rootfs_dir/etc/shadow

}

# install busybox
install_busybox()
{
    # refer to Busybox Config File For LXC
    cp -r $PREFIX/home/stb/* $PREFIX/$lxc_rootfs_dir/
    cp -r $PREFIX/usr/sbin/init.lxc $PREFIX/$lxc_rootfs_dir/usr/sbin/
    cp -r $PREFIX/sbin/iptables $PREFIX/$lxc_rootfs_dir/sbin/
    cp -r $PREFIX/sbin/xtables-multi $PREFIX/$lxc_rootfs_dir/sbin/
}


install_app()
{
    make -C $SDK_PATH/sample/lxc_ipc
    cp -f $SAMPLE_OUT_PATH/lxc_ipc/launch_app      $PREFIX/$lxc_rootfs_dir/home/ && \
    $STRIP $PREFIX/$lxc_rootfs_dir/home/launch_app
    cp -f $SAMPLE_OUT_PATH/lxc_ipc/msg_rcv_lxc2      $PREFIX/$lxc_rootfs_dir/home/ && \
    $STRIP $PREFIX/$lxc_rootfs_dir/home/msg_rcv_lxc2
	cat << EOF > $PREFIX/$lxc_rootfs_dir/home/lxc2_start.sh
#!/bin/sh
/home/msg_rcv_lxc2
EOF
    chmod ug+x $PREFIX/$lxc_rootfs_dir/home/lxc2_start.sh
}
# create and deploy lxc config file for CA debug
install_lxc_dbg_config()
{
    cat <<EOF > $PREFIX/$lxc_config_file
lxc.utsname = $name

#lxc.id_map = u 0 1000 10
#lxc.id_map = g 0 1000 10

lxc.cap.keep = net_raw net_admin setuid setgid

lxc.tty = 1
lxc.pts = 1
lxc.rootfs = $lxc_rootfs_dir
lxc.mount = $lxc_config_dir/fstab
lxc.pivotdir = /tmp/lxc_putold

lxc.mount.entry = shm dev/shm tmpfs rw,nosuid,nodev,noexec,mode=0660,create=dir 0 0
lxc.mount.entry = /dev/shm dev/shm none rw,bind 0 0
lxc.mount.entry = /dev/mem dev/mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/null dev/null none bind,optional,create=file 0 0
lxc.mount.entry = /dev/urandom dev/urandom none bind,optional,create=file 0 0
lxc.mount.entry = /dev/watchdog dev/watchdog none bind,optional,create=file 0 0

EOF
if [ "X${lxc_enable_net}" = "Xyes" ]; then
	:;
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
EOF

    chmod 644 $PREFIX/usr/var/lib/lxc/$name/config

    cat <<EOF > $PREFIX/$lxc_config_dir/fstab
proc            /home/$name/proc           proc    defaults        0       0
sysfs           /home/$name/sys            sysfs   defaults        0       0
tmp             /home/$name/tmp            tmpfs   nosuid,noexec,nodev,mode=1770        0       0
dev             /home/$name/dev            tmpfs   nosuid,noexec,nodev,mode=0770        0       0
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

lxc.cap.keep = net_raw net_admin setuid setgid
lxc.console = none

lxc.rootfs = $lxc_rootfs_dir
lxc.mount = $lxc_config_dir/fstab
lxc.pivotdir = /tmp/lxc_putold

lxc.mount.entry = shm dev/shm tmpfs rw,nosuid,nodev,noexec,mode=0660,create=dir 0 0
lxc.mount.entry = /dev/shm dev/shm none rw,bind 0 0
lxc.mount.entry = /dev/mem dev/mem none bind,optional,create=file 0 0
lxc.mount.entry = /dev/null dev/null none bind,optional,create=file 0 0
lxc.mount.entry = /dev/urandom dev/urandom none bind,optional,create=file 0 0
lxc.mount.entry = /dev/watchdog dev/watchdog none bind,optional,create=file 0 0

EOF
if [ "X${lxc_enable_net}" = "Xyes" ]; then
	:;
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
EOF

    chmod 644 $PREFIX/usr/var/lib/lxc/$name/config

    cat <<EOF > $PREFIX/$lxc_config_dir/fstab
proc            /home/$name/proc           proc    defaults        0       0
sysfs           /home/$name/sys            sysfs   defaults        0       0
tmp             /home/$name/tmp            tmpfs   nosuid,noexec,nodev,mode=1770        0       0
dev             /home/$name/dev            tmpfs   nosuid,noexec,nodev,mode=0770        0       0
EOF
    chmod 644 $PREFIX/$lxc_config_dir/fstab
}

##################################################################################
delete_unused_files()
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
install_app
delete_unused_files

if [ $LXC_MODE == "DEBUG" ]; then
    install_dbg_fs_scripts
    install_lxc_dbg_config
else
    install_rel_fs_scripts
    install_lxc_rel_config
fi

