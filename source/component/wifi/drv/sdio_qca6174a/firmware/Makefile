PWD := $(shell pwd)
all:
	#********************************qca6174**********************************
	test -d $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/wlan || mkdir -p $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/wlan
	cp -fv $(PWD)/qca_wifi_perf.sh $(ANDROID_PRODUCT_OUT)/system/bin/
	cp -fv $(PWD)/otp30.bin $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	cp -fv $(PWD)/utf30.bin $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	cp -fv $(PWD)/wlan/cfg.dat $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/wlan/
	cp -fv $(PWD)/wlan/qcom_cfg.ini $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/wlan/
	cp -fv $(PWD)/btfw30.tlv $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	cp -fv $(PWD)/btnv30.bin $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	cp -fv $(PWD)/bdwlan30.bin $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	cp -fv $(PWD)/qwlan30.bin $(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	
#	test -d $(ANDROID_PRODUCT_OUT)/system/bin || mkdir -p $(ANDROID_PRODUCT_OUT)/system/bin
#	cp -fv $(PWD)/test/bdtest $(ANDROID_PRODUCT_OUT)/system/bin/
	
	#test -d $(ANDROID_PRODUCT_OUT)/system/vendor/lib || mkdir -p $(ANDROID_PRODUCT_OUT)/system/vendor/lib
	#cp -fv $(PWD)/vendor/lib/libbtnv.so $(ANDROID_PRODUCT_OUT)/system/vendor/lib/
	


#	mkdir -p $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
#	cp -fv $(PWD)/athwlan.bin $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174
#	cp -fv $(PWD)/fakeboar.bin $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
#	cp -fv $(PWD)/otp.bin $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
#	cp -fv $(PWD)/utf.bin $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
#	cp -fv $(PWD)/wlan/cfg.dat $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/wlan/
#	cp -fv $(PWD)/wlan/qcom_cfg.ini $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/wlan/
#	cp -fv $(PWD)/btfw32.tlv $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
#	cp -fv $(PWD)/btnv32.bin $(PWD)/../../../../../../$(ANDROID_PRODUCT_OUT)/system/etc/firmware/qca6174/
	
#	test -d $(ANDROID_PRODUCT_OUT)/system/bin || mkdir -p $(ANDROID_PRODUCT_OUT)/system/bin
#	cp -fv $(PWD)/test/bdtest $(ANDROID_PRODUCT_OUT)/system/bin/
	
#	test -d $(ANDROID_PRODUCT_OUT)/system/vendor/lib || mkdir -p $(ANDROID_PRODUCT_OUT)/system/vendor/lib
#	cp -fv $(PWD)/vendor/lib/libbtnv.so $(ANDROID_PRODUCT_OUT)/system/vendor/lib/	
#	test -d $(ANDROID_PRODUCT_OUT)/system/lib || mkdir -p $(ANDROID_PRODUCT_OUT)/system/lib
#	cp -fv $(PWD)/../firmware/lib/libbt-vendor.so $(ANDROID_PRODUCT_OUT)/system/lib/
	
