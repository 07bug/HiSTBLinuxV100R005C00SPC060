��������: 
        1,��ʾ��ε���PDMģ��ĺ�������baseparam,logo,fastplay�����Ĳ���������.
        2,��ʾ��δӿ���logo����fastplay���ɵ�Ӧ���е�ͼ�λ���Ƶ����.
�����ʽ: 
        1,update parameter and data:
	Usage: sample_mce_update image_type file
        image_type: 1:baseparam, 2:logo, 3:fastplay(dvbֱ��ģʽ)
        example: sample_mce_update 1 null
        example: sample_mce_update 2 /mnt/test.jpg
        example: sample_mce_update 3 null

	2,transition :
	Usage: sample_mce_trans transtype [freq] [srate] [qamtype or polarization]
        transtype: 1:logo->graphics, 2:logo->video play, 3:fastplay->graphics, 4:fastplay->video play 
        example: sample_mce_trans 1 
        example: sample_mce_trans 2 3840 27500 0
        example: sample_mce_trans 3 
        example: sample_mce_trans 4 3840 27500 0
����˵��: see Usage.

ע������: ��flash�б������baseparam�������Լ�logo������fastplay������һ������������������