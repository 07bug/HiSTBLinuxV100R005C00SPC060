/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : logsys.h
  Version       : V1.0
  Author        : Hisilicon multimedia software group
  Created       : 
  Description   : interfaces in this file are used to debug, only output debug information, not
  				  effect on function;
  				  CNcomment:���ļ�ʵ�ֵĵ��Խӿ���Ϊģ����϶�λʹ�ã��������ⲿ���������Ϣ��
				  CNcomment:����ģ�鱾��Ĺ�������κ�Ӱ�죬������ģ���ڲ�ʹ�ú궨��Ϊ�յķ�ʽ
				  CNcomment:�������Ρ����Բ���32������ĵ�����Ϣ����趨��ʹ��UDP�˿���Ϊ����
				  CNcomment:���ն˿ڣ�������Ϣ�Ĵ�ӡ��ʽ��printf������ǰ����Ӽ������õĺ궨��
				  CNcomment:�����������ģ��Ϊ������ģ�飬�����Ҫ���������DebugOutString��Ҫ
				  CNcomment:���ͬ��������Ϣ���ֵ��Ӧ����500���ֽڣ����򽫳�����������--Խ�� 
  History       :
  1.Date        : 
    Author      : rxc
    Modification: 

******************************************************************************/
#ifndef _LOSYS_H
#define _LOSYS_H

//#define LOW_WINDOWS_ON        1     //WINDOWS switch
#define LOW_LINUX_ON            1     //LINUX switch

/*****************************************************************************************
*                            head file                                                     * 
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>

#ifdef LOW_LINUX_ON
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <netdb.h>
    #include <sys/ioctl.h>
    #include <net/if.h>
    #include <sys/utsname.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>

    #define SOCKET int
#endif

#ifdef LOW_WINDOWS_ON
   #include <Winsock2.h>
/*****************************************************************************************
*                    define error CONST                                                   * 
*****************************************************************************************/
   #define ENOTSOCK           95     /* Socket operation on non-socket */
   #define EDESTADDRREQ       96     /* Destination address required */
   #define EMSGSIZE           97     /* Message too long */
   #define EPROTOTYPE         98     /* Protocol wrong type for socket */
   #define ENOPROTOOPT        99     /* Protocol not available */
   #define EPROTONOSUPPORT   120     /* Protocol not supported */   //
   #define ESOCKTNOSUPPORT   121     /* Socket type not supported */
   #define EOPNOTSUPP        122     /* Operation not supported on transport endpoint */
   #define EAFNOSUPPORT      124     /* Address family not supported by protocol */
   #define EADDRINUSE        125     /* Address already in use */
   #define EADDRNOTAVAIL     126     /* Cannot assign requested address */
   #define ENETDOWN          127     /* Network is down */
   #define ENETUNREACH       128     /* Network is unreachable */
   #define ENETRESET         129     /* Network dropped connection because of reset */
   #define ECONNABORTED      130     /* Software caused connection abort */
   #define ECONNRESET        131     /* Connection reset by peer */
   #define ENOBUFS           132     /* No buffer space available */
   #define EISCONN           133     /* Transport endpoint is already connected */
   #define ENOTCONN          134     /* Transport endpoint is not connected */
   #define ESHUTDOWN         143     /* Cannot send after transport endpoint shutdown */
   #define ETIMEDOUT         145     /* Connection timed out */
   #define ECONNREFUSED      146     /* Connection refused */
   #define EHOSTUNREACH      148     /* No route to host */
   #define EALREADY          149     /* Operation already in progress */
   #define EINPROGRESS       150     /* Operation now in progress */
   #define EWOULDBLOCK    EAGAIN     /* Operation would block */
//error.h
   #define EINTR               4     /* Interrupted system call */
   #define EAGAIN             11     /* Try again */
   #define EACCES             13     /* Permission denied */
   #define EFAULT             14     /* Bad address */
   #define EINVAL             22     /* Invalid argument */
   #define EMFILE             24     /* Too many open files */
//just windows 
   #define ENOTINITIALISED   200     //WSANOTINITIALISED   socket
   
#if 0
    #define IP_ADD_MEMBERSHIP   5           /* add  an IP group membership      */
    #define IP_DROP_MEMBERSHIP  6           /* drop an IP group membership      */
	struct ip_mreq {
		struct in_addr  imr_multiaddr;	   /* IP multicast address of group */
		struct in_addr  imr_interface;     /* local IP address of interface */
	};
#endif
/*****************************************************************************************
*                            define other CONST                                           * 
*****************************************************************************************/
   #define MSG_WAITALL  0x10
   #define MSG_DONTWAIT 0x11    

/*****************************************************************************************
*                            type definition                                             *
*****************************************************************************************/
#endif

#ifndef NULL
//#define NULL (void*)0
#endif

#ifndef BOOL
//#define BOOL int
#endif

#ifndef TRUE
//#define TRUE  1
#endif

#ifndef FALSE
//#define FALSE 0
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT32
#define INT32 int
#endif

#ifndef INT16
#define INT16 short
#endif

/*****************************************************************************************
*                             interface declare                                          *
*****************************************************************************************/	   
//socket function

/**************************************************************************
* Function Name:My_getsockerr
* Description:  get information about last wrong operation on socket
*				CNcomment:��ȡ�ϴ��й�socket��������ľ�����Ϣ,
* Parameters:no
* Return:error code
***************************************************************************/
int My_getsockerr(void);

/**************************************************************************
* Function Name:My_socket
* Description:create SOCKET
* Parameters:
*			af:	 address description, only AF_INET is supported now
*				 CNcomment:��ַ������Ŀǰ��֧��AF_INET
*           type:
*				 socket type; TCP use SOCK_STREAM, UDP use SOCK_DGRAM;
*				 SOCK_RAW and SOCK_RDM SOCK_SEQPACKET are also supported but shielded hereon
*				 CNcomment:�׽��ֵ�����  
*   	         CNcomment:TCP�׽���ΪSOCK_STREAMֵ  
*		         CNcomment:UDP�׽���ΪSOCK_DGRAMֵ 
*           	 CNcomment:ע��SOCK_RAW SOCK_RDM SOCK_SEQPACKET Ҳ��֧�֣��ڴ���ʱ����   
*           protocol:
*				 socket protocol, only zero is supported now
*				 CNcomment:�׽������õ�Э��,Ŀǰֻ��Ϊ0
* Return:   socket handle:success; -1:failure;
*			CNcomment:�ɹ������׽�����������ʧ�ܷ���-1
*           CNcomment:ע���û�����ͨ������My_getsockerr����������йش���ľ�����Ϣ
***************************************************************************/
int My_socket(int domain, int type, int protocol);

/**************************************************************************
* Function Name:My_setsockopt
* Description:  set socket option
*				CNcomment:����SOCKET��ѡ��
* Parameters:
*			s:
*				socket handle;
*				CNcomment:�׽���������
*           level:  option level, only support SOL_SOCKET
*					CNcomment:ѡ��Ĳ�Σ���ʱ�̶�ΪSOL_SOCKET 
*   	    optname:
*					option name
*					SO_DEBUG	:record debug information is permit
*                   SO_BROADCAST:transport broadcast message is permit
*                   SO_REUSEADDR:reuse local address is permit
*                   SO_KEEPALIVE:keep link is permit
*                   SO_DONTROUTE:message can be send without passing router
*                   SO_LINGER	:close is delay if there is data
*                   SO_OOBINLINE:receive outter data in inner is permit
*                   SO_SNDBUF	:set the size of send buffer
*                   SO_RCVBUF	:set the size of receive buffer
*                   SO_ERROR	:permit to get or clean error on socket

*					CNcomment:ѡ������� 
*                   CNcomment:SO_DEBUG �������¼������Ϣ
*                   CNcomment:SO_BROADCAST�������͹㲥��Ϣ
*                   CNcomment:SO_REUSEADDR�������ص�ַ����
*                   CNcomment:SO_KEEPALIVE�����������ӻ�Ծ
*                   CNcomment:SO_DONTROUTE������������Ϣ������·��ѡ��
*                   CNcomment:SO_LINGER����������ݴ��ڣ���ô�رձ���ʱ
*                   CNcomment:SO_OOBINLINE�������ڴ��ڽ��մ�������
*                   CNcomment:SO_SNDBUF�����÷������ݵĻ����С
*                   CNcomment:SO_RCVBUF�����ý������ݵĻ����С
*                   CNcomment:SO_ERROR����socket�ϻ�ú��������
*		    optval:
*					porint to option buffer
*					CNcomment:ָ�����ڻ�ȡ�����õ�ѡ��ֵ�Ļ���ռ� 
*           optlen:
*					buffer size
*					CNcomment:����ռ�ĳ���
*			Note:you can consult setsocket description in windows or linux to get more information
*           CNcomment:ע���������庬�������WINDOWS��LINUX��setsockopt����˵��
* Return:
*			0:success; -1:failure;
*           CNcomment:ע���û�����ͨ�����á���������������йش���ľ�����Ϣ
***************************************************************************/
int My_setsockopt(int s, int level, int optname, void *optval, int optlen);

/**************************************************************************
* Function Name:My_connect
* Description:	create connect
* Parameters:	sockfd:socket;     						CNcomment:���������׽��ֵ�������
*           	serv_addr:socket address on server;		CNcomment:�û���Ҫ���ӵķ������˵��׽��ֵĵ�ַ  
*   	    	addrlen:size of address;				CNcomment:��ַ�ĳ���  
* Return:		0:success; -1:failure;
*          	 	CNcomment:ע���û�����ͨ�����á���������������йش���ľ�����Ϣ
***************************************************************************/
int My_connect(int sockfd,  const struct sockaddr *serv_addr, int addrlen);

/**************************************************************************
* Function Name:My_recv
* Description:	receive data from stream socket;		CNcomment:����ʽ�׽����н�������
* Parameters:	
*				s:socket;								CNcomment:���������׽��ֵ�������
*           	buf:buffer;								CNcomment:ָ��������ݵĻ�������ָ��  
*   	    	len:buffer size;						CNcomment:�������Ĵ�С   
*           	flags:control option;					CNcmoomnt:����ѡ��
*                  CNcomment:MSG_OOB�����մ�������
*                  CNcomment:MSG_PEEK���鿴�׽��ֵ����ݣ����������ݴ��׽��ֻ�������ȡ��
*                  CNcomment:MSG_DONTWAIT������׽��ֻ��������㹻�ռ䣬�������ȴ�
*                  CNcomment:MSG_WAITALL������׽��ֻ��������㹻�ռ䣬�����ȴ�
*                  CNcomment:ע������ 0�����κο���
* Return:		success: received data number(byte);
*				-1:error;
*				CNcomment:�ɹ������ؽ��յ��ֽ���
*           	CNcomment:connect�رգ�����0    
*           	CNcomment:���󣺷���-1
*           	CNcomment:ע���û�����ͨ�����á���������������йش���ľ�����Ϣ
***************************************************************************/
int My_recv(int s, void *buf, int len, int flags);

/**************************************************************************
* Function Name:My_recvfrom
* Description:	receive data from datagram socket;		CNcomment:�����ݱ��׽����н�������
* Parameters:
*				s:socket:								CNcomment:���������׽��ֵ�������
*           	buf:receive buffer;						CNcomment:ָ��������ݵĻ�������ָ��  
*   	    	len:buffer size;						CNcomment:�������Ĵ�С   
*           	flags:control option;					CNcomment:����ѡ��
*                  CNcomment:MSG_OOB�����մ�������
*                  CNcomment:MSG_PEEK���鿴�׽��ֵ����ݣ����������ݴ��׽��ֻ�������ȡ��
*                  CNcomment:MSG_DONTWAIT������׽��ֻ��������㹻�ռ䣬�������ȴ�
*                  CNcomment:MSG_WAITALL������׽��ֻ��������㹻�ռ䣬�����ȴ�
*                  CNcomment:ע������ 0�����κο���
*           	from:address of send socket;			CNcomment:�������ݱ��׽��ֵĵ�ַ
*           	fromlen:size of address
* Return:		success: received data number(byte);
*				-1:error;
*				CNcomment:�ɹ������ؽ��յ��ֽ���
*           	CNcomment:connect�رգ�����0    
*           	CNcomment:���󣺷���-1
*           	CNcomment:ע���û�����ͨ�����á���������������йش���ľ�����Ϣ
***************************************************************************/
int My_recvfrom(int s, void *buf, int len, int flags, struct sockaddr *from, int *fromlen);

/**************************************************************************
* Function Name:My_closesocket
* Description:	close socket
* Parameters:	s:socket neet to close
*          		CNcomment:������Ϊ��setsockopt���õ�ѡ�����
* Return:		0 :success    
*           	-1: failure  
*           	CNcomment:ע���û�����ͨ�����á���������������йش���ľ�����Ϣ 
***************************************************************************/
int My_closesocket(int s);

/**************************************************************************
* Function Name:My_sendto
* Description	send data to datagram socket;			CNcomment:�����ݱ��׽����з�������
* Parameters:	
*				s:socket;								CNcomment:���������׽��ֵ�������
*           	buf:send buffer;						CNcomment:ָ�������ݵĻ�������ָ��  
*   	    	len:buffer size;						CNcomment:�������Ĵ�С   
*           	flags:control option;					CNcomment:����ѡ��
*                  CNcomment:MSG_OOB�����մ�������
*                  CNcomment:MSG_PEEK���鿴�׽��ֵ����ݣ����������ݴ��׽��ֻ�������ȡ��
*                  CNcomment:MSG_DONTWAIT������׽��ֻ��������㹻�ռ䣬�������ȴ�
*                  CNcomment:ע������ 0�����κο���
*           	to:address of receive socket;			CNcomment:�������ݱ��׽��ֵĵ�ַ
*           	tolen:sizo of address
* Return:		success: send data number(byte);
*				-1:error;
*				CNcomment:�ɹ������ؽ��յ��ֽ���
*           	CNcomment:���󣺷���-1
*           	CNcomment:ע���û�����ͨ�����á���������������йش���ľ�����Ϣ
***************************************************************************/
int My_sendto(int s, void *buf, int len, int flags, const struct sockaddr *to, int tolen);

/**************************************************************************
* Function Name:My_send
* Description:	send data to stream socket;				CNcomment:����ʽ�׽����з�������
* Parameters:
*				s:socket;								CNcomment:���������׽��ֵ�������
*           	buf:send buffer;						CNcomment:ָ�������ݵĻ�������ָ��  
*   	    	len:buffer size;						CNcomment:�������Ĵ�С   
*           	flags:control option;					CNcomment:����ѡ��
*                  CNcomment:MSG_OOB�����մ�������
*                  CNcomment:MSG_PEEK���鿴�׽��ֵ����ݣ����������ݴ��׽��ֻ�������ȡ��
*                  CNcomment:MSG_DONTWAIT������׽��ֻ��������㹻�ռ䣬�������ȴ�
*                  CNcomment:MSG_WAITALL������׽��ֻ��������㹻�ռ䣬�����ȴ�
*                  CNcomment:0�����κο���
* Return:		success: send data number(byte);
*				-1:error;
*				CNcomment:�ɹ������ؽ��յ��ֽ���
*           	CNcomment:���󣺷���-1
***************************************************************************/
int My_send(int s, void *buf, int len, int flags);


//string function
/**************************************************************************
* Function Name:My_strcasecmp
* Description:	compare two string, char is sensitivity;	CNcomment:�Ƚ�ָ����Χ���ַ�����С,�������ַ����Ĵ�Сд
* Parameters:	string1:string1
*           	string2:string2
* Return:		>0:string1>string2
*           	0 :string1=string2
*				<0:string1<string2
***************************************************************************/
int My_strcasecmp(const char *string1, const char *string2);

/**************************************************************************
* Function Name:My_strncasecmp
* Description:	compare two string, char is sensitivity;	CNcomment:�Ƚ�ָ����Χ���ַ�����С,�������ַ����Ĵ�Сд
* Parameters:	string1:string1
*           	string2:string2
*           	count:count of char to compare
* Return:		>0:string1>string2
*           	0 :string1=string2
*				<0:string1<string2
***************************************************************************/
int My_strncasecmp(const char *string1, const char *string2, size_t count);

//system time function
/**************************************************************************
* Function Name:My_getsystime
* Description:	get system time;		CNcomment:���ϵͳ��ʱ��ֵ 
* Parameters:	no
* Return:		return the time(ms);	CNcomment:����ϵͳ��ʱ��ֵ����λ����
***************************************************************************/
unsigned int My_getsystime(void);

/**************************************************************************
* Function Name:My_gettimeofday
* Description:	get system time;			CNcommont:���ϵͳ�ĵ�ǰʱ��ֵ����timeval�ṹ����
* Parameters:	timeofday:time structure:	CNcomment:��ȡ��ʱ��ֵ
* Return:		0:success; oters:failure;
***************************************************************************/
int My_gettimeofday(struct timeval *timeofday);

/**************************************************************************
* Function Name:My_Sleep
* Description:	sleep;				CNcomment:����ָ����ʱ�䵥λ 
* Parameters:	sleep time(ms);		CNcomment:ָ��ʱ�䵥λ������
* Return:no
***************************************************************************/
void My_Sleep(unsigned short uSleep);

/**************************************************************************
* Function Name:My_drand48
* Description:get a double precision random;	CNcomment:��ȡһ��˫�����������
* Parameters:no
* Return:random
***************************************************************************/
double My_drand48(void);

/**************************************************************************
* Function Name:My_createMutex
* Description:	create a mutex;		CNcomment:����һ�������ź���
* Parameters:	no
* Return:		0: falure; others:mutex ID
***************************************************************************/
int My_createMutex(void);

/**************************************************************************
* Function Name:y_freeMutex
* Description:	free a mutex;	CNcomment:ɾ��һ�������ź���
* Parameters:	mutex ID
* Return:no
***************************************************************************/
void My_deleteMutex(int mutexID);

/**************************************************************************
* Function Name:My_enterMutex
* Description:get a mutex, enter protect area;		CNcomment:��ȡһ�������źţ����뱣���׶�
* Parameters:	mutex ID
* Return:no
***************************************************************************/
void My_enterMutex(int mutexID);

/**************************************************************************
* Function Name:My_leaveMutex
* Description:	release a mutex, leave protect area;	CNcomment:�ͷ�һ�������źţ��뿪�����׶�
* Parameters:	mutex ID
* Return:no
***************************************************************************/
void My_leaveMutex(int mutexID);
/**************************************************************************
* Function Name:My_strstr
* Description:	find a string
*				CNcomment:�����ַ�������linux c�������з�װ����������������飬��ֹ�Ƿ�����
* Parameters:	haystack:target string pointer;    	CNcomment:ָ��Ŀ���ַ�����ָ��
*           	needle:string will be search;		CNcomment:ָ��Ҫ���ҵ��ַ�����ָ��
* Return:		
*				NULL:not find; 
*				others:pointer point to the string find in target string
***************************************************************************/
char *My_strstr(const char *haystack,const char *needle);
/**************************************************************************
* Function Name:My_strchr
* Description:  search char
*				CNcomment:�����ַ�����linux c�������з�װ����������������飬��ֹ�Ƿ�����
* Parameters:	s:target string pointer;    CNcomment:ָ��Ŀ���ַ�����ָ��
*           	c:char will be search;		CNcomment:Ҫ���ҵ��ַ�
* Return:		
*				NULL:not find; 
*				others:pointer point to the char find in target string
***************************************************************************/
char * My_strchr(const char *s, int c);
#endif

