��������: չʾ��Ƶ��·track�������ܣ�track����avplay�󶨣�ֱ����track��PCM֡��
�����ʽ: ./sample_mixengine file0 TrackWeight0 [SampleRate0] [Channel0] file1 TrackWeight1 [SampleRate1] [Channel1] ......
����˵����file0 ��0�������ļ�����
          TrackWeight0 ��0��track��Ȩ�� ȡֵ��Χ0~100
          SampleRate0  ��0������pcm�����Ĳ����� ��λ��Hz ȡֵ��Χ 80000|11025|12000|16000|22050|24000|320000|44100|48000|88200|96000|176400|192000
          channel0     ��0������pcm������������ ȡֵ��Χ 1|2
          file0 ��1�������ļ�����
          TrackWeight1 ��1��track��Ȩ�� ȡֵ��Χ0~100
          SampleRate1  ��1������pcm�����Ĳ����� ��λ��Hz ȡֵ��Χ 80000|11025|12000|16000|22050|24000|320000|44100|48000|88200|96000|176400|192000
          channel1     ��1������pcm������������ ȡֵ��Χ 1|2          
��    ��: ./sample_mixengine a.wav 100 48000 1 b.wav 100 48000 1


��������: չʾ��Ƶ��·track�������ܣ�track��avplay��
�����ʽ: ./sample_audio_mix freq srate inputfile0 type0 inputfile1 type1 ...
����˵����freq Ƶ��Ƶ��  ��λ KHz
	  srate ������
          inputfile0   ��0�������ļ�����
          type0        ��0�������ļ��ı�������
          inputfile1   ��1�������ļ�����
          type1        ��1�������ļ��ı�������       
��    ��: ./sample_audio_mix 618 6187 a.mp3 mp3 b.aac aac
