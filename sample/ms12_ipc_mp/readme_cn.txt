��������һ��չʾ����TS�����Ź���(֧��ѡ��MS12����ͨ·)
�����ʽ��sample_tsplay_ms12 file [vo_format] [bUseMS12]
����˵����file��ts�ļ�·��
          [vo_format]�������ʽ��ȡֵΪ1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50��ȱʡֵΪ1080i_50
		  [bUseMS12]:  �Ƿ�ѡ��MS12����ͨ·��ȡֵΪ 0 Adec����ͨ·��1 MS12����ͨ·��
		               ע��MS12֧��AAC/DDP��ƵЭ�飬�����Ƶ����Э�飬MS12����ͨ·��֧�֣����Զ�ѡ��Adec����ͨ·��
����ο���sample_tsplay ./test.ts 1080i_50 1          

MS12����ͨ·ѡ����ԣ�
    sample�ο������������ѡ��MS12����ͨ·�ķ������ɺ�ROUTE_MS12_METHOD_A/ROUTE_MS12_METHOD_B���ƣ��û����Բο���
	ROUTE_MS12_METHOD_A�������鷽����
	                     ʶ������Format�������û���Ը��������ӦMS12��Formatת����ת��֮ǰ��Ҫ��ѯϵͳ�Ƿ�֧�ָ�MS12 Format��
	                     ���磺ʶ�𵽵�Format��FORMAT_AAC��,����Ҫ�л���MS12����ͨ·���Ȳ�ѯFORMAT_MS12_AAC�Ƿ�֧�֣���֧�ֽ�FORMAT_AAC�޸�ΪFORMAT_MS12_AAC��
	ROUTE_MS12_METHOD_B��
	                     ʶ������Format����ת��Ϊ��ƵCodecID�󣬸����û���Ը��������ӦMS12 CodecIDת�����۸ģ���ת��֮ǰ��Ҫ��ѯϵͳ�Ƿ�֧�ָ�MS12 Format��	                     
                             ���磺ʶ�𵽵�Format��FORMAT_AAC��,��ת��ΪAudioCodecID��HA_AUDIO_ID_AAC��������Ҫ�л���MS12����ͨ·���Ȳ�ѯFORMAT_MS12_AAC�Ƿ�֧�֣���֧�ֽ�HA_AUDIO_ID_AAC�޸�ΪHA_AUDIO_ID_MS12_AAC�� 

						 
������������չʾ����MS12��·���Ź���
�����ʽ��sample_ms12_mixer ts_file  [tts tts_file] [system uiaudio_file]
����˵����file��ts�ļ�·��
          tts:  ����tts����ͨ·
          system������ui audio����ͨ·
		  
����ο�: ./sample_ms12_mixer ./test.ts 
          ./sample_ms12_mixer null tts ./tts_48k_2ch.pcm
          ./sample_ms12_mixer null system  ./uiaudio_48_2ch.pcm
          ./sample_ms12_mixer ./test.ts  tts ./tts_48k_2ch.pcm system ./uiaudio_48_2ch.pcm

