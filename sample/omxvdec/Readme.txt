sample_omxvdecʹ�÷�����

һ��Ŀ�� 
     ������֤OMX����ͨ�������Բ���OMX��vfmw��vpss����ͨ���Ƿ��ܹ���������������������sample_esplay��  

	 
����ʹ�÷���

Linux������

1��linux�����£�ϵͳĬ�ϲ�����OMXģ���KO,������Ҫ�ֶ����أ�insmod /kmod/hi_omxvdec.ko, Ȼ���� Code/sample/omxvdec
   ·���£�ֱ�� make�� ���Եõ�sample_omxvdec�Ĳ��Գ���

2���ڴ������룺
	./sample_omxvdec  filename1 filename2 ...
	
	�س�ȷ������Ҫѡ�����������Э�����ͣ������������Ĳ����ļ��ж��������Ҫ���ѡ���Ӧ����������Э�����͡�
	
Android������	
	android������omx����Ĭ�ϱ����kernel����sample_omxvdec�����Ѿ����� /usr/bin ·���£����Կ���ֱ�����У�
	
	sample_omxvdec  filename1 filename2 ...
	 
	 
������֤��׼
  
    ����sample_omxvdec�޷����Ż��棬���Բ���ͨ�������Ż������ж��Ƿ���ȷ���롣
������Խ������д�ӡ��
	
	**********...TEST SUCCESSFULL...*********
	
���������ͨ�����������ǲ��ܱ�֤ÿһ֡�Ƿ���붼��ȷ������ͨ����yuv�ķ�ʽ���鿴���������
	
OMX��yuv������
	
	����ǰ��  echo save_yuv start >/proc/msp/omxvdec	
	���Ժ�  echo save_yuv stop >/proc/msp/omxvdec
 	Ĭ�ϴ洢��/mnt·���¡�
	  