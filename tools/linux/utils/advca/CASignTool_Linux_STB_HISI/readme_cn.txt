
˵��
1.��������CASignTool.exeǩ�����ߵ�linux�汾
2.������ʹ��cfg�ı�����������Ϣ(�ļ����ɸ���)
3.Ŀǰ���߲�֧�ָ���·���д��ڿո�
4.ʹ�÷�ʽ���£�

  1>./CASignTool 0 ../cfg/Signboot_config.cfg
  ��ǩ��Key����
  �������Key�ļ�·��������д��Root_private_key_file��External_public_key_file����Root_private_key_file��BootFile�Ķ���֮һ�����߻��ǩ��Key����BootFile�����������fastboot.bin����keyarea.bin

  ����δǩ���İ�ȫBoot��
  ������ROOT_RSA_Private_Key������external priv key��external pub key�����ɸ�������ͳ�Key������������ǩ��
  
  ǩ����Key���������������
  ������ROOT_RSA_Private_Key��external pub key��������external priv key��������������ľ���ǩ��
  
  ǩ��������
  ��Signboot_config.cfg����chiptype, key file, cfg.bin, msid, version, inputdir, outputdir ����Ϣ��ǩ������������OutputFileDir�������õ�Ŀ¼��
  
  ����-k -b -r -o��ѡ�����ö�Ӧ��key�ļ���boot���Դ�ļ�������ļ���·��
  
  2>./CASignTool 1 ../cfg/merge_config.cfg
  �ϲ������ļ�Ϊ���յ�boot
  ��merge_config.cfg����chiptype, ��ǩ�� bin �ļ�, inputdir, outputdir ����Ϣ���ϳ�final boot������OutputFileDir�������õ�Ŀ¼��

  ���� -r -o��ѡ�����ö�Ӧ��Դ�ļ�������ļ���·��

  3>./CASignTool 2 -K KeyFilePath -R srcFilePath -O outputFilePath [-h 1|2] [-ss sectionsize] [-ys 1|0]
  ��BOOT����common��ʽǩ����
  ����-Kָ��ǩ����BOOT���������ǩ����Կ��-Rָ����ǩ���ľ�������·����-Oָ������ļ�����Ŀ¼��-hָ��ǩ����ʽ��1Ϊsha1��2Ϊsha256�������ָ������Ĭ��Ϊsha256��-ssָ���ֶ�ǩ���ķֶδ�С�����簴1MB��С�ֶ�ǩ������ָ��Ϊ-ss 1�������ָ����ָ��Ϊ0���򲻷ֶ�ǩ����-ysָ���ļ�ϵͳ��Ϊ1��Ϊyaffs�ļ�ϵͳ��Ϊ0��ָ����Ĭ��ΪNONE.

  ����-k -r -o��ѡ�����ö�Ӧ��key�ļ���Դ�ļ�������ļ���·��

  4>   ./CASignTool 3 special_merge_config.cfg -m m -K KeyFilePath -r srcDirPath -O destFilePath
   ����./CASignTool 3 special_single_config.cfg -m s -K KeyFilePath -r srcDirPath -o destDirPath
  ��boot����special��ʽǩ����
  
  �ϲ�ģʽ
  �������ļ��У�ImageNumber����Ϊ��Ҫǩ���ľ�����������һ��ǩ����������ImageXXX,OffsetofImageXXX��XXXΪ���������������ӡ��������в�������-mָ��ǩ��ģʽ��ָ��Ϊm���ϲ�ģʽ��-Kָ��ǩ����Կ����·����-rָ����ǩ���������ڵ�·����-Oָ���ϲ�����ǩ���������ڵ�·��
  
  ��һ����ǩģʽ
  �������ļ��У�ImageNumber����Ϊ��Ҫǩ���ľ�����������һ��ǩ����������ImageXXX��XXXΪ���������������ӡ��������в�������-mָ��ǩ��ģʽ��ָ��Ϊs����һģʽ��-Kָ��ǩ����Կ����·����-rָ����ǩ���������ڵ�·����-oָ���ϲ�����ǩ���������ڵ�Ŀ¼
      
  5>./CASignTool 4 crypto_config.cfg [-it t/b -ot t/b] [-K KeyFilePath] -R srcFilePath -O destFilePath
  ��boot������ܺͽ��ܡ�
  ��crypto_config.cfg����AES Key��IV��������Ϣ������-Kָ��RSA��sha1��sha2ǩ���������Կ����·����-Rָ�������ļ�����·����-Oָ������ļ�����·����
    ˵���� ��Ҫ������Ҫ����crypto_config.cfg�еĲ���������AES���ܣ�һ����Ҫ���ü����㷨Algorithm������ģʽMode������˽ԿKey����IV������ͬʱ���ӽ��ܲ�����Ҫ��-itָ�������ļ��ĸ�ʽ����-otָ������ļ��ĸ�ʽ��t����txt��b����bin.

  6>./CASignTool 7 ../cfg/verifyboot.cfg
  ��֤Finalboot��
  ��verifyboot.cfg����Finalboot����root pub key��msid��version��msidmask��versionmask���Ƿ�Ϊ���ܾ��񡢼�����Կ����Ϣ����֤FinalBoot�Ƿ�Ϊ��ȷ���ɡ�

  7>./CASignTool 8 eValue keyDestPath
  ����RSA��Կ��
  ��������eValue���Լ���Կ����Ŀ¼keyDestPath����������Կ���ɵ���Կ����Ŀ¼
   
5.�����ļ�������ļ�������cfg�ļ���������

6.boot����ǩ��ʱ��֧�ֵ�оƬ����Hi3798CV200,Hi3798MV100,Hi3716MV420,Hi3716MV410,Hi3796MV100,Hi3796MV200,Hi3798MV200,Hi3716DV110,Hi3716DV100����cfg�ļ������ã���boot����������оƬ�޹ء�
7.cfg�ļ��Զ�ȥ����#��ͷ��ע����
8.����������������ѯ
