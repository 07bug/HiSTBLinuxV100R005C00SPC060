#===========================================================================
#input wayland dir
#===========================================================================
echo -n "please input wayland dir: example for \"/home/y00181162/007-STB-SDK/SDK_SVN_V1R2/trunk/BBIT-Test/Code/source/component/wayland\""
echo ""
echo "dir:"
read wayland_dir
#===========================================================================
#product pc bin file
#===========================================================================
sed -i "s/# WL_PRODUCT_FILE := y/WL_PRODUCT_FILE := y/"   base.mak
make clean WL_DIR=$wayland_dir; make WL_DIR=$wayland_dir
sed -i "s/WL_PRODUCT_FILE := y/# WL_PRODUCT_FILE := y/"   base.mak

#===========================================================================
#compile weston
#===========================================================================
make clean WL_DIR=$wayland_dir;make WL_DIR=$wayland_dir
