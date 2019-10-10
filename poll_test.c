#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "errno.h"
#include "sys/socket.h"
#include "poll.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "poll_test.h"


int main(int argc,char **argv)
{
	printf("socket之poll测试\n");
	server_poll_create(1,3);	
	return 0;
}

int server_poll_create(int fd,int POLLNUM)
{
	struct pollfd pollfd_array[POLLNUM];
	nfds_t fdnum = 0;
	int rv = 0;
	int i;
	int connectfd = -1;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;	

	/*初始化poll_struct*/
	for(i = 0;i < POLLNUM;i++)
	{
		pollfd_array[i].fd = -1;
	}

	pollfd_array[0].fd = fd;
	pollfd_array[0].events = POLLIN;

	/*查找出结构体数组中有效描述符的个数*/
	for(i = 0;i < POLLNUM; i++)
	{
		if(pollfd_array[i].fd != -1)
		{
			fdnum++;
		}
	}
	rv = poll(pollfd_array,fdnum,-1);//永远阻塞
	if(rv < 0)
	{
		printf("server socket poll error:%s\n",strerror(errno));
		close(fd);//关闭套接字
		exit(0);
	}
	else
	{
		/*判断是否是新的套接字(客户端)连接过来*/
		if(pollfd_array[0].revents & POLLIN)
		{
			connectfd = accept(pollfd_array[0].fd,(struct sockaddr *)&client_addr,&client_addr_len);
			if(connectfd < 0)
			{
				printf("server poll accept error:%s\n",strerror(errno));
				close(pollfd_array[0].fd);
				exit(0);
			}
			else
			{
				printf("server poll accept client[%s:%d]successfully.\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
				/*将连接描述符添加到pollfd_arrsy中，以便监测*/
				for(i = 1;i < POLLNUM;i++)
				{
					if(pollfd_array[i].fd < 0)
					{
						pollfd_array[i].fd = connectfd;
						pollfd_array[i].events = POLLIN;
						break;
					}
				}
			}
		}
		/*寻找发生事件的socket描述符*/
		else
		{
			for(i = i;i < fdnum;i++)
		
			if(pollfd_array[i].revents & POLLIN)
			{

			}
		}
	}

}
