1.Ŀ¼�ṹ��
1) adapter/����ҪӦ�ó��������һЩ�ӿ�
	int fv_is_first_enter(int *first);
		����ӿ������ж��Ƿ��ǵ�һ���ϵ�
	void fv_clear_first_enter(void);
		����ӿ����������һ���ϵ��־		
	void fv_factory_reset(void);
		����ӿ����ڻָ���������
	#define MAX_VERSION_LEN (64)
		����궨���˰汾���ֶ���󳤶�
	void fv_get_sdk_version(char *buf, int *sz);
		����ӿ����ڻ�ȡsdk�汾��
	void fv_get_app_version(char *buf, int *sz);
		����ӿ����ڻ�ȡapp�汾��
	void fv_get_plat_version(char *buf, int *sz);
		����ӿ����ڻ�ȡƽ̨�汾��
	
2) configs/: ��Ҫ�ͻ������һЩ����
	#define VIDEO_FILE_NAME "video.ts"
		��������
	#define DDR_DETECT_DRV	"/root/ddr.ko"
		ddr��С�������
	#define CONFIG_FILE_NAME "/root/config.ini"	
		�����ļ����·��(���ļ���)
	#define UDISK_MOUNT_POINT "/mnt"
		U�̹��ص�
	#define FV_CONF_LANG_ZH
		�������ʱ��������ʾ���ģ�Ĭ�������Ľ��棬ע�͵�֮�������lable��ʾΪӢ��
	
	#define IR_VOL_PLUS_KEY	              (0x3ec1ff00)
		�����������ֵ
	#define IR_VOL_DEC_KEY	              (0x6699ff00)
		������С����ֵ
	#define IR_RESET_FACTORY_KEY	       (0x639cff00)
		�ָ��������ü���ֵ

	#define KEYLED_TYPE (0)
		ǰ�������
		
	#define MAX_TUNER_NR	1
		��������tuner������
	#define TUNER_SECTION	"tuner"
		�����ļ���tuner section�ؼ���
	#define	FREQ_KEY	"freq" 
		tuner��ƵƵ������
	#define SYMBOL_RATE_BAND_KEY	"symbol_rate_or_band"
		�����ʻ��ߴ�������,�Ƿ����ʻ��Ǵ���ȡ����tuner��������
	#define MODE_TYPE_POLAR_KEY	"mode_type_or_polar"
		qam���Ʒ�ʽ��������,ȡ����tuner����
	#define REVERSE_KEY	"reverse"
		Ƶ�׵��ô���ʽ,��tuner�������ó�CABһ��ʱ��Ч
	
2.ʹ�ý���	
	
1) ���𵽵���
	/root
    	������ config.ini     ������ configs/config.ini
    	������ ddr.ko         ; ���� drivers/ddr.ko
    	������ hifv           ; ���� out/hifv
    	������ res        
    	��   ������ DroidSansFallbackLegacy.ttf ; ���� sample/res/font/DroidSansFallbackLegacy.ttf
    	
    	���Ҫ��֤����Ƶ���Ź��ܣ�����Ҫ����������Ƶ�ļ�����Ϊvideo.ts��������u�̵ĵ�һ��fat�����ϡ�   
	
2)ʹ�ã�
	����ǿ�ִ���ļ�hifv��ִ��hifv���ɡ������Ҫǿ�ƽ��볧�⣬ִ��hifv 1��
