1��sample_aenc
��������: չʾ���빦��(�ϲ�Ӧ���ṩ��Ƶ������)
�����ʽ: ./sample_aenc infileName inChannel insamplerate outfileName outfileType
����˵����infileName    �������Դ�ļ����� (pcm/wav��ʽ)
          inChannel     ���������� (��֧��1��2) 
          insamplerate  ��������� (��������ʷ�Χ��8000-192000) 
          outfileName   ��������ݱ�����ļ�����
          outfileType   ����ļ��������� (֧��aac/g711/amrnb/amrwb)
��    ��: ./sample_aenc ./boys_48kHz_stereo_16.wav 2 48000 ./boys.aac aac
ע�������Ҫָ���������Դͨ�����Ͳ����ʣ�����λ���֧��16bit

2��sample_aenc_track
��������: չʾaac���빦��(aenc��track�İ�)
�����ʽ: ./sample_aenc_track infile intype outfile outtype
����˵����infile    �������Դ�ļ�����
          intype    �������Դ����
          outfile   ��������ݱ�����ļ�����
          outtype   ����󱣴���ļ����� 
��    ��: ./sample_aenc_track ./qgw.mp3 mp3 ./qgw.aac aac
ע�������֧���������Դ����aac/mp3/dts/dra/mlp/pcm/ddp(ac3/eac3)
