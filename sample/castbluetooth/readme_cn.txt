���ܣ�
     1����ʾCast�����ݺ�ʹ����������������Ƶ���ݻ������ܡ�
	 2��ʹ������ң���������������ԣ��Զ����ӻ������ܡ�
     
������
     ʹ��sampleǰ����Ҫȷ��bluetooth��ط����Ѿ�������

�÷���
     1)�� /etc/init.d/S90modules Ŀ¼����ӣ�. bluez_init
	    #!/bin/sh
	    telnetd&
	    cd /kmod
	    ./load
	    . bluez_init
		
     2)��LD_LIBRARY_PATH����������ALSA��������·��/usr/share/bluetooth/lib/
     	 export LD_LIBRARY_PATH="/usr/share/bluetooth/lib/:$LD_LIBRARY_PATH"
      3)ʹ��sample_esplay���Ÿ���������Cast��ȡ��Ƶ���ݡ�

     4)ִ��./sample_bluetooth��������������
       ʾ����./sample_bluetooth 
	  Please select the bluetooth function:
      0 -- Exit.
      1 -- Pair.
      2 -- Paired devices.
      3 -- Connected headset.
      4 -- Adapter control.
     ���У�ѡ��1����������������ԡ�ѡ��2�鿴�Ѿ���Գɹ������������豸��״̬��ѡ��3�鿴�Ѿ���������״̬�����������豸��
	 ѡ�� 1���г���ʼ������������豸�Լ�������������״̬������s��ʼɨ���豸����ʱ���������豸Ӧ���������״̬��ɨ����Ϻ���г�ɨ�赽�������豸��
	 Sample_BT_Pairing(), 154: Pair bluetooth device start.
	 Sample_BT_Pairing(), 164: Get bluetooth adapter success, hci0  00:18:E4:0A:4A:E2
	 Input char 's' to scan the bluetooth device.
	 s
	 Sample_BT_ScanDevice(), 85: Scan bluetooth device start.
	 Scan bluetooth device success, 3 devices are available, please select:
	 0  BC:14:EF:02:49:2B  [unknown]  not paired
	 1  00:0A:94:80:21:FC  LB-08  paired
     2  00:0C:8A:B3:AC:EC  Bose Mini SoundLink  paired
	 ѡ����Ҫ��Ե������豸��ѡ��1����ʾ���00:0A:94:80:21:FC�豸����������0000.��ʾ��Գɹ��󲢷��ص�һ��Ŀ¼��
	 1
     Sample_BT_Pairing(), 178: Find bluetooth device , 00:0A:94:80:21:FC  LB-08
	 please input the bluetooth device password:
     0000
     Sample_BT_Pairing(), 190: Pair the bluetooth device success.

     Please select the bluetooth function:
      0 -- Exit.
      1 -- Pair.
      2 -- Paired devices.
      3 -- Connected headset.
      4 -- Adapter control.
      ѡ��2�г��Ѿ���Գɹ����豸��ѡ��0��ʾҪ��00:0A:94:80:21:FC����豸�������ӡ�Ȼ��ѡ��2�������ӡ�
	  2
      Sample_BT_PairedDevices(), 245: Get bluetooth adapter success, hci0  00:18:E4:0A:4A:E2
      Get paired bluetooth device success, 2 devices are available, please select:
      0: addr [00:0A:94:80:21:FC], name [LB-08], class [3], status [0]
      1: addr [00:0C:8A:B3:AC:EC], name [Bose Mini SoundLink], class [3], status [0]
	  0
	  Please select the operation :
      0 -- Exit.
      1 -- Status.
      2 -- Connect.
      3 -- Disconnect.
      4 -- Remove.
      5 -- SetTrust��
	  
	  2
	  input: 00:0A:94:80:21:FC as /devices/virtual/input/input0
	  arrd 00:0A:94:80:21:FC
	  Sample_BT_PairedDevices(), 334: Connect bluetooth device success.
	  Please select the operation :
      0 -- Exit.
      1 -- Status.
      2 -- Connect.
      3 -- Disconnect.
      4 -- Remove.
	  5 -- SetTrust��
	  
	  ���ӳɹ�������0���ص�һ��Ŀ¼��ѡ��2�鿴�Ѿ����ӵ��豸����ʱҲ����ѡ�����ӵ��ĸ��豸�Ͽ���
	  0
	  
	  �������������ң������������5, �����豸Ϊ�������豸��
	  ��ң���������������ѣ��رպ����������������ȣ�ң�����������Զ����ӣ��������������
	  
     Please select the bluetooth function:
      0 -- Exit.
      1 -- Pair.
      2 -- Paired devices.
      3 -- Connected headset.
      4 -- Adapter control.

	  2
	  Sample_BT_PairedDevices(), 245: Get bluetooth adapter success, hci0  00:18:E4:0A:4A:E2
      Get paired bluetooth device success, 2 devices are available, please select:
      0: addr [00:0A:94:80:21:FC], name [LB-08], status [0]
      1: addr [00:0C:8A:B3:AC:EC], name [Bose Mini SoundLink], status [1]
	  ����Э��֧��ͬʱ���Ӷ���豸����������3�鿴�Ѿ������豸��
	  3
	  adapter : 00:18:E4:0A:4A:E2 hci0
      headset : 00:0C:8A:B3:AC:EC Bose Mini SoundLink

      Please select the bluetooth function:
      0 -- Exit.
      1 -- Pair.
      2 -- Paired devices.
      3 -- Connected headset.
      4 -- Adapter control.
	  
  
    5)ִ��./sample_castbluetooth
	  ʹ�������������Ÿ�������sample֧�����������豸�л�������ִ�д�sampleǰ���Ƚ����������������Ӻá�
	  ʾ����./sample_castbluetooth 
	   ����"K"��ʼ���š�����"S"ֹͣ���š�������"c"�л������豸��������"K"��ʼ���ţ���ʱ��һ�������豸������
	        # ./sample_castbluetooth 
		    please input c to change config
		    please input the k to start cast!, s to stop and deinit
			k
			please input c to change config
			please input the k to start cast!, s to stop and deinit
			s
			please input c to change config
			please input the k to start cast!, s to stop and deinit
			c
			pcm.bluetooth{
				type bluetooth
				device 00:0A:94:80:21:FC
				}
		   please input c to change config
		   please input the k to start cast!, s to stop and deinit
		   k
		   please input c to change config
		   please input the k to start cast!, s to stop and deinit
    

ע�⣺
	1��ִ������ǰӦ��֤���������Ѿ�������ʹ��ps -ef�鿴�Ƿ������½��̡�
	   1000      1346     1  0 00:00 ?        00:00:00 dbus-daemon --config-file=/usr/share/bluetooth/etc/dbus-1/system.conf
       root      1348     1  0 00:00 ?        00:00:00 bluetoothd --udev
    2��sample_castbluetooth��֧�����������豸���л���
	3��sample_castbluetoothͨ������ALSA�������ļ����ﵽ�л������豸��Ŀ�ġ�
	   ��һ�����ӳɹ��������豸MAC��ַ�������/etc/bluetooth/FirstConf/asound.conf��
	   �ڶ������ӳɹ��������豸MAC��ַ�������/etc/bluetooth/SecondConf/asound.conf��
	   ���������ӳɹ��������豸MAC��ַҲ�������/etc/bluetooth/FirstConf/asound.conf���Ӷ����ǵ�һ�����ӳɹ���Mac��ַ��
	   



	

    
    