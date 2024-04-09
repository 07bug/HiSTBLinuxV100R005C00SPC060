/*
 * FileName:
 * Author:         sdk  Version: 1.0.0  Date: 2014-11-10
 * Description: tee logcat
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include<signal.h>
#include<sys/types.h>
#include <log/logger.h>
#include <log/logd.h>
#include <log/logprint.h>
#include <log/event_tag_map.h>
#include <cutils/sockets.h>
#include <sys/stat.h>
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/mman.h> /*for mmap*/
#include <securec.h>
#include "tc_ns_client.h"
/* #define tlogd */
#include "tee_log.h"


/*for ioctl*/
#define AID_SYSTEM			1000
#define __TEELOGGERIO			0xBE
#define TEELOGGER_GET_LOG_LEVEL		_IO(__TEELOGGERIO, 1) /* get the TEE log level */
#define TEELOGGER_SET_LOG_LEVEL		_IO(__TEELOGGERIO, 2) /* set the TEE log leve */

#ifdef LOGGER_ENTRY_MAX_LEN
#undef LOGGER_ENTRY_MAX_LEN
#endif
#define LOGGER_ENTRY_MAX_LEN		1024

#define LOG_FILE_LIMIT			(500*1024)  /* log file size limit */


#define NAME_SIZE	256
#define NAME_NUM	3
#define NAME_LIMITS	64
static const char log_name_attr[NAME_NUM][NAME_SIZE] = {
	"/data/hisi_logs/running_trace/teeos_logs/teeOS_log-1",
	"/data/hisi_logs/running_trace/teeos_logs/teeOS_log-2",
	"/data/hisi_logs/running_trace/teeos_logs/teeOS_log-3"
};
static int	m_dev_fd;
static int	m_tee_log_fd;
static uint32_t	m_logsize;
static FILE	*m_file;
static bool	m_name_flag;
/* check weather /data/hisi_logs  and /data/hisi_logs/running_trace and /data/hisi_logs/teeos_logs exist, if not exist just create the folder*/
int32_t log_dir_check()
{
	int ret = 0;
	struct stat statbuf_dir;
	/* check the "hisi_logs" dir is exist or not ,if not create */
	ret = stat("data/hisi_logs", &statbuf_dir);	/*lint !e838 */
	if (ret != 0) {
		ret = mkdir("data/hisi_logs", S_IRWXU | S_IRWXG);
		if (ret != 0) {
			tloge("failed to mkdir data/hisi_logs:errno is %d\n", errno);
			return -1;
		}
		ret = chown("data/hisi_logs", (uid_t)-1, AID_SYSTEM);
		if (ret < 0)
			tloge("chown err\n");
		ret = chmod("data/hisi_logs", 0770);
		if (ret < 0)
			tloge("chmod err\n");
	}
	/* check the "running_trace" dir is exist or not ,if not create */
	ret = stat("data/hisi_logs/running_trace", &statbuf_dir);
	if (ret != 0) {
		ret = mkdir("data/hisi_logs/running_trace", S_IRWXU | S_IRWXG);
		if (ret != 0) {
			tloge("failed to mkdir data/hisi_logs/running_trace:errno is %d\n", errno);
			return -1;
		}
		ret = chown("data/hisi_logs/running_trace", (uid_t)-1, AID_SYSTEM);
		if (ret < 0)
			tloge("chown err\n");
		ret = chmod("data/hisi_logs/running_trace", 0770);
		if (ret < 0)
			tloge("chmod err\n");
	}

	/* test the "teeos_logs" dir is exist or not ,if not create */
	ret = stat("data/hisi_logs/running_trace/teeos_logs", &statbuf_dir);
	if (ret != 0) {
		ret = mkdir("data/hisi_logs/running_trace/teeos_logs", S_IRWXU | S_IRWXG);
		if (ret != 0) {
			tloge("mkdir data/hisi_logs/running_trace/teeos_logs:errno %d\n", errno);
			return -1;
		}
		ret = chown("data/hisi_logs/running_trace/teeos_logs", (uid_t)-1, AID_SYSTEM);
		if (ret < 0)
			tloge("chown err\n");
		ret = chmod("data/hisi_logs/running_trace/teeos_logs", 0770);
		if (ret < 0)
			tloge("chmod err\n");
	}
	tlogd("data/hisi_logs/running_trace/teeos_logs exist\n");
	return 0;
}
/* if the m_logsize of current log file  is over the LOG_LIMIT,
rename old log file, and create new "log_name_attr[0]" */
int32_t log_overflow()
{
	uint32_t i;
	int ret = 0;

	if (m_file) {
		fclose(m_file);
		m_file = 0;
	}

	ret = log_dir_check();	/*lint !e838 */
	if (ret != 0) {
		tloge("teeos log dir does not find, ret = %d\n", ret);
		return -1;
	}
	for (i = 2; i > 0; i--) {
		if (access(log_name_attr[i - 1], F_OK) == 0) {
			if (rename(log_name_attr[i - 1], log_name_attr[i])) {/* [false alarm]:
								only system users can modify */
				tloge("logsize_over rename error, errno is %d\n", errno);
				return -1;
			}
		}
	}

	m_file = fopen(log_name_attr[0], "w+");
	if (m_file == NULL) {
		tloge("get_logfile fcreate is error\n");
		ret =  -1;
		return ret;
	}
	ret = chown(log_name_attr[0], (uid_t)-1, AID_SYSTEM);/* [false alarm]:only system
							user can modify */
	if (ret < 0)
		tloge("chown error\n");
	ret = chmod(log_name_attr[0], S_IRUSR | S_IWUSR | S_IRGRP);
	if (ret < 0)
		tloge("chmod error\n");

	m_tee_log_fd = fileno(m_file);
	m_logsize = 0;
	return ret;
}



const char m_logfile_path[] = {"/data/hisi_logs/running_trace/teeos_logs/"};
/* get the log file's FILE */
int32_t log_getfile(char *filename)
{
	tlogd("save tee log start ++\n");
	int ret = 0;
	struct stat stat_buff;
	char name[NAME_SIZE] = {0};
	errno_t rc = EOK;

	if (m_file) {
		fclose(m_file);
		m_file = 0;
	}

	ret = log_dir_check();	/*lint !e838 */
	if (ret != 0) {
		tloge("teeos log dir does not find, ret = %d\n", ret);
		return -1;
	}

	if (filename == NULL) {
		tlogd("filename is null\n");
		m_file = fopen(log_name_attr[0], "a+");
		if (m_file == NULL) {
			tloge("failed to open %s, errno is %d\n", log_name_attr[0], errno);
			return -1;
		}
		ret = chown(log_name_attr[0], (uid_t)-1, AID_SYSTEM);/* [false alarm]:only system users
									can modify */
		if (ret < 0)
			tloge("chown error\n");
		ret = chmod(log_name_attr[0], S_IRUSR | S_IWUSR | S_IRGRP);
		if (ret < 0)
			tloge("chmod error\n");
	} else {
		if (strstr(filename, "../"))
			return -1;

		size_t full_filename_len = strlen(m_logfile_path) + strlen(filename);
		if (sizeof(name) <= full_filename_len) {
			tlogd("the file path is too long: %d\n", (int)full_filename_len);
			return -1;
		}
		rc = snprintf_s(name, sizeof(name), sizeof(name) - 1,
			"%s%s", m_logfile_path, filename);
		if (-1 == rc) {
			tlogd("snprintf failed: %d\n", rc);
			return -1;
		}

		tlogd("filename is %s  name is %s\n", filename, name);

		m_name_flag = true;
		m_file = fopen(name, "a+");/* [false alarm]:only system users can modify */
		if (m_file == NULL) {
			tloge("failed to open %s, errno is %d\n", name, errno);
			return -1;
		}
		ret = chown(name, (uid_t)-1, AID_SYSTEM);/* [false alarm]:only system users can modify */
		if (ret < 0)
			tloge("chown error\n");
		ret = chmod(name, S_IRUSR | S_IWUSR | S_IRGRP);/* [false alarm]: save with above */
		if (ret < 0)
			tloge("chmod error\n");
	}

	m_tee_log_fd = fileno(m_file);

	ret = fstat(m_tee_log_fd, &stat_buff);
	if (ret) {
		tloge("fstat error\n");
		fclose(m_file);
		return -1;
	}
	m_logsize = (uint32_t)stat_buff.st_size;

	tlogd(" m_tee_log_fd=%d m_logsize=%d ,ret=%d\n", fileno(m_file), m_logsize, ret);
	return 0;
}

static int memory_func()
{
	TEEC_Context context;
	TEEC_Session session;
	TEEC_Result result;
	TEEC_UUID global_uuid = TEE_SERVICE_GLOBAL;
	TEEC_Operation operation;
	uint32_t origin = 0;
	uint32_t cmd = GLOBAL_CMD_ID_TEE_INFO;
	errno_t rc = EOK;

	result = TEEC_InitializeContext(NULL, &context);
	if (result != TEEC_SUCCESS) {
		goto cleanup_1;
	}

	result = TEEC_OpenSession(
			 &context,
			 &session,
			 &global_uuid,
			 TEEC_LOGIN_PUBLIC,
			 NULL,
			 NULL,
			 NULL);
	if (result != TEEC_SUCCESS) {
		tloge("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
		goto cleanup_2;
	}

	rc = memset_s(&operation, sizeof(operation), 0, sizeof(operation));
	if (EOK != rc) {
		tloge("memset_s failed, %d\n", rc);
		goto cleanup_3;
	}

	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES(
				       TEEC_VALUE_INOUT,
				       TEEC_NONE,
				       TEEC_NONE,
				       TEEC_NONE);	/*lint !e845 */
	operation.params[0].value.a = 0;
	operation.params[0].value.b = 1;

	result = TEEC_InvokeCommand(
			 &session,
			 cmd,
			 &operation,
			 &origin);
	if (result != TEEC_SUCCESS)
		tloge("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);

	printf("memory use:\n");
	printf("    global-  %u/10000\n", operation.params[0].value.a);
	printf("    teeos-   %u/10000\n", operation.params[0].value.b);

cleanup_3:
	TEEC_CloseSession(&session);
cleanup_2:
	TEEC_FinalizeContext(&context);
cleanup_1:
	return (int)result;
}

static int  log_setlevel(int level)
{
	int ret;
	ret = ioctl(m_dev_fd, TEELOGGER_SET_LOG_LEVEL, level);	/*lint !e835 !e845 */
	return ret;
}

static int log_getlevel()
{
	int ret = 0;
	ret = ioctl(m_dev_fd, TEELOGGER_GET_LOG_LEVEL, NULL);	/*lint !e838 !e835 !e845 */
	return ret;
}

void help_show()
{
	printf("this is help, you should input:\n");
	printf("    -f:  save teeos log to /data/teeos_logs/teeOS_log-1, 2 and 3 \n");
	printf("          -flog.txt:  save teeos log to /data/teeos_logs/log.txt , file name shoud be less 64\n");
	printf("    -g:  get tee log level \n");
	printf("    -s:  set tee log level \n");
	printf("          -s1:  set tee log level to be 1, you can input 0,1,2,3,4 \n");
	printf("    -m: get tee memory status \n");
}

void f_func(bool flag, char *filename)
{
	int tlog_dev_fd = 0;
	int result = 1;
	int ret = 0;
	fd_set readset;
	char read_buff[1025] = {0};

	tlogd("f_func\n");
	tlog_dev_fd = m_dev_fd;		/*lint !e838 */
	if (flag)
		if (log_getfile(filename)) {
			tloge("failed to get teelog file\n");
			exit(EXIT_FAILURE);
		}
	while (1) {	/*lint !e716 */
		do {
			FD_ZERO(&readset);
			FD_SET((unsigned int)tlog_dev_fd, &readset);
			tlogd("while select\n");
			result = select((tlog_dev_fd + 1), &readset, NULL, NULL, NULL);
		} while (result == -1 && errno == EINTR);
		if (result >= 0) {
			if (FD_ISSET((unsigned int)tlog_dev_fd, &readset)) {
				ret = read(tlog_dev_fd, read_buff, LOGGER_ENTRY_MAX_LEN);
				if (ret < 0) {
					if (errno == EINTR) {
						tloge("step 1 =-----errno == EINTR-----\n");
					}
					if (errno == EAGAIN) {
						tloge("step 2 =-----errno == EAGAIN-----\n");
					}
					tloge("tlogcat read ret=%d\n", ret);
					exit(EXIT_FAILURE);
				} else if (!ret) {
					tloge("read: Unexpected EOF!\n");
					exit(EXIT_FAILURE);
				} else {
					tlogd("read length. ret = %d \n", ret);
				}

				read_buff[ret] = '\0';
				if (flag) {
					if ((m_logsize > LOG_FILE_LIMIT) && !m_name_flag) {
						ret = log_overflow();
						if (ret != 0) {
							tloge("failed to get tlog file fd, ret is %d\n", ret);
							exit(EXIT_FAILURE);
						}
					}
					size_t numm;
					numm = fwrite(read_buff, 1, (size_t)ret, m_file);
					(void)fflush(m_file);

					if ((int)numm < ret) {
						tloge("fwrite error!log_fd=%d!fileno=%d!\n",
							m_tee_log_fd, fileno(m_file));

						if (log_getfile(filename)) {
							tloge("when write retry,failed to get teelog file\n");
							exit(EXIT_FAILURE);
						}
						numm = fwrite(read_buff, 1, (size_t)ret, m_file);
						(void)fflush(m_file);
					}

					m_logsize += numm;
				} else
					printf("%s\n", read_buff);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	printf("tlogcat start ++ \n");
	int ch;
	int ret = 0;
	bool default_op = true;

	m_dev_fd = open("/dev/hisi_teelog",  O_RDONLY);
	if (m_dev_fd < 0) {
		tloge("open log device error\n");
		goto error1;
	} else
		tlogd("open dev success m_dev_fd=%d\n", m_dev_fd);

	while ((ch = getopt(argc, argv, "f::ms:gh")) != -1) {
		default_op = false;
		tlogd("optind: %d,argc:%d,argv[%d]:%s\n", optind, argc, optind, argv[optind]);
		switch (ch) {
		case 'm':
			printf("HAVE option: -m\n\n");
			memory_func();
			break;
		case 'f':
			printf("HAVE option: -f\n");
			tlogd("The argument of -f is %s len should less %d\n", optarg, NAME_LIMITS);
			if (optarg != NULL)
				if (strlen(optarg) > NAME_LIMITS) {
					tloge("filename len is error, name shoud be less %d\n", NAME_LIMITS);
					goto error;
				}
			f_func((bool)true, optarg);
			break;
		case 's':
			printf("HAVE option: -s\n");
			tlogd("The argument of -s is %s\n", optarg);
			if (!optarg)
				goto error;
			if ((strlen(optarg) > 1) || *optarg > '4' || *optarg < '0') {
				tloge("invalid log level, should be 0~4.\n");
				goto error;
			}
			int level;
			level = atoi(optarg);
			ret = log_setlevel(level);
			printf("New level is %d, ret=%d \n", level, ret);
			break;
		case 'g':
			tlogd("HAVE option: -g\n");
			ret = log_getlevel();
			printf("tee log level is %d\n", ret);
			break;
		case 'h':
			printf("HAVE option: -h\n");
			help_show();
			break;
		default:
			printf("Unknown option: %c\n", (char)optopt);
			help_show();
			break;
		}

		printf("----------------------------\n");
		tlogd("optind=%d,argv[%d]=%s\n", optind, optind, argv[optind]);
	}

	if (default_op)
		f_func((bool)false, optarg);
	printf("tlogcat end --\n");
	close(m_dev_fd);
	return 0;
error:
	help_show();
	close(m_dev_fd);
error1:
	return 0;
}

