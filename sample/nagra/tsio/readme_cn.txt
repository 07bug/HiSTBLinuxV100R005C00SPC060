����������չʾ��TSIO�ı���TS�����Ź���
�����ʽ��sample_tsio_tsplay file [vo_format]
����˵����file��ts�ļ�·��
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
����ο���sample_tsio_tsplay ./test.t

����������չʾ��TSIO��DVB���Ź���
�����ʽ��sample_tsio_dvbplay freq srate [qamtype or polarization] [vo_format]
����˵����freq����ƵƵ��(MHz)
          srate: ������(kbps)
          [qamtype or polarization]: ��ѡ�DVB-C����ʱΪqamtype����ʾQAM���Ʒ�ʽ��DVB-S����ʱΪpolarization����ʾ��������
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
����ο���sample_tsio_dvbplay 618 6875 64 720p_50

����������չʾ��TSIO��bulk��������
�����ʽ��sample_tsio_bulk file
����˵����file��bulk�ļ�·��
����ο���sample_tsio_bulk ./test.bulk