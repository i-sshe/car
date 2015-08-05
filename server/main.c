#include "server.h"
//#include "drive.h"


#define FAIL 	(-1)
#define PORT 	8888
#define SA		struct sockaddr
#define SA_IN	struct sockaddr_in


int main(int argc, char *argv[])
{
	int		sockfd = 0;
	int		newfd = 0;	
	int		openfd = 0;
	int	 	err = 0;
	char	c;								//用來接收信息	
	SA_IN	servaddr;
	SA_IN	clieaddr;
	socklen_t	addrlen;

	//socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == FAIL)
	{
		fprintf(stderr, "socket error:%s\n", strerror(errno));
		exit(-1);
	}

	//填充結構信息
	memset(&servaddr, 0, sizeof(servaddr));			//填充sizeof(servaddr)個0
	servaddr.sin_family 	= AF_INET;
	servaddr.sin_port 		= htons(PORT);
	servaddr.sin_addr.s_addr= htonl(INADDR_ANY);

	//bind
	addrlen = sizeof(SA_IN);						//這裏可能不對
	if (bind(sockfd, (SA *)&servaddr, addrlen) == FAIL)
	{
		fprintf(stderr, "bind error:%s\n", strerror(errno));
		exit(-1);
	}

	//listen
	if (listen(sockfd, 5) == FAIL)				//可用MSGSIZE = 1024,最大連接數
	{
		fprintf(stderr, "listen error:%s\n", strerror(errno));
		exit(-1);
	}
	
	fprintf(stderr, "準備accept!\n");

	openfd = open("/dev/car", O_RDWR);
	printf("openfd = %d\n", openfd);
	
	
	while (1)
	{
		//accept
		if ((newfd = accept(sockfd, (SA *)&clieaddr, &addrlen)) == FAIL)
		{
			fprintf(stderr, "accept error:%s\n", strerror(errno));
			exit(-1);
		}

		while (1)
		{
			if (recv(newfd, &c, sizeof(char), 0) == FAIL)
			{
				fprintf(stderr, "recv error:%s\n", strerror(errno));
				exit(-1);
			}
			else 
			{
				printf("recv the massage is : %c \n", c);
			}


			if ((c == 'q') || (c == 'l'))
			{
				if (write(openfd, &c, 1) < 0)
				{
					printf("write error!\n");
				}
				else
				{
					printf("wirte \'%c\'\n", c);
				}
				
				break;						//跳出循環
			}
			else if ((c == 'w') || (c == 's') || (c == 'a') || (c == 'd'))
			{
				if (write(openfd, &c, 1) < 0)
				{
					printf("write error!\n");
				}
				else
				{
					printf("wirte \'%c\'\n", c);
				}
			}
			else
			{
				continue;
			}
		}
		
		close(newfd);
		
		if (c == 'l')
		{
			break;							//跳出死循環
		}
	}

	close(sockfd);

	return 0;

}
