echo 1 > /sys/bus/cpu/devices/cpu0/online
echo 1 > /sys/bus/cpu/devices/cpu1/online
echo 1 > /sys/bus/cpu/devices/cpu2/online
echo 1 > /sys/bus/cpu/devices/cpu3/online
echo performance > /sys/bus/cpu/devices/cpu0/cpufreq/scaling_governor
echo performance > /sys/bus/cpu/devices/cpu1/cpufreq/scaling_governor
echo performance > /sys/bus/cpu/devices/cpu2/cpufreq/scaling_governor
echo performance > /sys/bus/cpu/devices/cpu3/cpufreq/scaling_governor

nums=524288
echo "Have $nums"
echo $nums > /proc/sys/net/core/wmem_max
echo $nums > /proc/sys/net/core/wmem_default
echo $nums > /proc/sys/net/core/rmem_max
echo $nums > /proc/sys/net/core/rmem_default
echo "10240 87380 $nums" > /proc/sys/net/ipv4/tcp_rmem
echo "10240 87380 $nums" > /proc/sys/net/ipv4/tcp_wmem
echo "$nums $nums $nums" > /proc/sys/net/ipv4/tcp_mem
echo 131072 > /proc/sys/net/ipv4/tcp_limit_output_bytes
echo 1 > /proc/sys/net/ipv4/route/flush
echo 0 > /proc/sys/net/ipv4/tcp_sack
echo "Enable WiFi high performance mode."

