����������չʾDVB��ȫ���Ź���
�����ʽ��sample_tee_dvbplay freq srate [qamtype or polarization] [vo_format]
����˵����freq����ƵƵ��(MHz)
          srate: ������(kbps)
          [qamtype or polarization]: ��ѡ�DVB-C����ʱΪqamtype����ʾQAM���Ʒ�ʽ��DVB-S����ʱΪpolarization����ʾ��������
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
����ο���./sample_tee_dvbplay 618 6875 64 720p_50

����������չʾ����TS����ȫ���Ź���
�����ʽ��sample_tee_tsplay file [vo_format]
����˵����file��ts�ļ�·��
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
����ο���sample_tee_tsplay ./test.ts 720p_50

��������: չʾ���л���ȫ���Ź��ܣ�1·��ȫ����+1·�ǰ�ȫ���ţ�
�����ʽ: sample_tee_tsplay_pip tsfile_0 tsfile_1 [vo_format] 
����˵����tsfile_0����һ��ts�ļ�·��
          tsfile_1: �ڶ���ts�ļ�·��
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
����ο���sample_tee_tsplay_pip ./test0.ts ./test1.ts 720p_50

��������: hisilicon ������ ��Hello, Secure World�� ��̬ta��ca����
�����ʽ: sample_tee_demo 0
����ο���sample_tee_demo 0

��������: hisilicon ������ ��Hello, Secure World�� ��̬ta��ca����
�����ʽ: sample_tee_dynamic_demo 0
����ο���sample_tee_dynamic_demo 0