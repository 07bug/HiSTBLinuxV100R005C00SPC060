����������
	��ʾuserproc�Ľӿ����ʹ�á�
�����ʽ: 
	./sample_userproc
ʹ��˵��:
	����'HI_PROC_AddDir'��'HI_PROC_RemoveDir'�ֱ����Դ�����ɾ��procĿ¼����Ŀ¼���ᱻ������/proc/hisiĿ¼����${NAME_INPUT}_${PID}�ķ�ʽ������
	����'HI_PROC_AddEntry' ��'HI_PROC_RemoveEntry'�ֱ����Դ�����ɾ��proc�ļ���
	ͨ��ע��'HI_PROC_SHOW_FN'�ص����ܹ�֧��ͨ��'cat /proc/hisi/your_dir_pid/your_entry'�ڻص�������ͨ��'HI_PROC_Printf'�����Ϣ�������û���
	ͨ��ע��'HI_PROC_CMD_FN'�ص����ܹ�֧��ͨ��'echo params [...] > /proc/hisi/your_dir_pid/your_entry'�ڻص������д����û��������Ϣ��
	userproc���֧���ڡ�HI_PROC_SHOW_FN����ͨ��'HI_PROC_Printf'���4KB����־��Ϣ��