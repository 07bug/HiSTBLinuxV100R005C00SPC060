����������չʾ����TS�����Ź���
�����ʽ��sample_tsplay file [vo_format]
����˵����file��ts�ļ�·��
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
����ο���sample_tsplay ./test.ts 720p_50

����������չʾ����TS�������첥�Ź���
�����ʽ��sample_tsplay_multiaud file [vo_format]
����˵����file��ts�ļ�·��
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50          
����ο���sample_tsplay_multiaud ./test.ts 720p_50
�����л������ųɹ�����������"c"��չʾ�����л�����

����������չʾָ������ƵPID��Ŀ������TS�����Ź���
�����ʽ��sample_tsplay_pid file vo_format vpid vtype apid atype
����˵����file��ts�ļ�·��
          vo_format�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
          vpid: ��Ƶpid
          vtype: ��ƵЭ�����ͣ�ȡֵΪmpeg2��mpeg4��h263��sor��vp6��vp6f��vp6a��h264��avs��real8��real9��vc1
          apid: ��Ƶpid
          atype: ��ƵЭ�����ͣ�ȡֵΪaac��mp3��dts��dra��mlp��pcm��ddp(ac3/eac3)          
����ο���sample_tsplay_pid ./test.ts 720p_50 100 mpeg2 101 mp3      