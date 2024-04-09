It is for LE environment myftm.

Note:  If your WLAN driver use the backports, then you need to copy backports's nl80211.h to libtcmd/
and Modify file "libtcmd/nl80211_drv.h" to include the local nl80211.h


For auto load WLAN driver, you need to add "-e 2" in the begining of the parameter. 
myftm -M 8 -r 15 -f 5210 -c 0 -p 14 -a 1 -t 3
