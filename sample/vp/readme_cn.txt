1. sample_vp_usbcam
����������չʾUSB����ͷ������Դ�����£����ӵ绰��Ƶ����
�����ʽ��sample_vp_usbcam cam_format af_inet local_IP remote_IP [vo_format]
����˵����cam_format ����ͷ�����ʽ ȡֵ��Χ 0|1 1��ʾYUV��ʽ��0��ʾMJPEG��ʽ
          af_inet    �������ͣ�ȡֵ��Χ 0|1 1��ʾIPv4�� 0��ʾIPv6
          local_IP   ����IP��ַ
          remote_IP  Զ��IP��ַ
          vo_format  ��Ƶ�����ʽ ȡֵ��Χ 1080P_60|1080P_50|1080i_60|1080i_50|720P_60 ��ѡ Ĭ��ֵ720P_50
��    �ӣ�sample_vp_usbcam 1 1 192.168.1.2 192,168.1.3 720P_50
          sample_vp_usbcam 1 0 fe80::228:1ff:fe19:777 fe80::228:2ff:fe19:777 720p_50
ע�����ȷ��USB����ͷ����ȷ����

2. sample_vp_vi
����������չʾVI������Դ�����£����ӵ绰��Ƶ����
�����ʽ��sample_vp_vi af_inet local_IP remote_IP [vo_format]
����˵����af_inet    �������ͣ�ȡֵ��Χ 0|1 1��ʾIPv4�� 0��ʾIPv6  
          local_IP   ����IP��ַ
          remote_IP  Զ��IP��ַ
          vo_format  ��Ƶ�����ʽ ȡֵ��Χ 1080P_60|1080P_50|1080i_60|1080i_50|720P_60 ��ѡ Ĭ��ֵ720P_50
��    �ӣ�sample_vp_vi 1 192.168.1.1 192,168.1.2 720P_50
          sample_vp_usbcam 0 fe80::228:1ff:fe19:777 fe80::228:2ff:fe19:777 720p_50
ע������μ�sample/vi/readme_cn.txtע������