/******************************************************************
 *文件:main.c
 *主要函数:main
 *函数主要功能:创建一个TCP客户端,用于pc端,发送控制命令.
 *注意:编译要加-lcurses选项
 *2015.5.12********************************************************


#include "client.h"


#define FAIL (-1)
#define PORT 8888
//#define SERVER_ID "127.0.0.1"				//只要改一下應該就可以!!!
#define SERVER_ID "192.168.1.17"			//arm板的ID

#define SA_IN 	struct sockaddr_in
#define SA		struct sockaddr
#define SH		struct hostent
/*
typedef struct sockaddr_in SA_IN;
typedef struct sockaddr	 SA;
typedef struct hostent	 SH;
*/

int main(void)
{
	int		sockfd = 0;
	SA_IN	servaddr;
	SH		*host;
	char 	c;

	if ((host = gethostbyname(SERVER_ID)) == NULL)
	{
		fprintf(stderr, "gethostbyname error:%s\n", strerror(h_errno));
		exit(-1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == FAIL)
	{
		fprintf(stderr, "socket error:%s\n", strerror(errno));
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(SA_IN));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr = *(struct in_addr*)host->h_addr;			//

	if (connect(sockfd, (SA *)&servaddr, sizeof(SA_IN)) == FAIL)
	{
		fprintf(stderr, "connect error:%s\n", strerror(errno));
		exit(-1);
	}

	initscr();										//清屏.
	while (1)
	{
		refresh();	
		c = getch();
		endwin();
//		c = getchar();
//		fflush(stdin);						//
		if (send(sockfd, &c, sizeof(char), 0) == FAIL)
		{
			fprintf(stderr, "send error:%s\n", strerror(errno));
			exit(-1);
		}
		else
		{
			fprintf(stderr, "發送的字符爲:%c\n", c);
		}

		if ((c == 'q') || (c == 'l'))
		{
			break;
		}
	}

	close(sockfd);

	return 0;
}
