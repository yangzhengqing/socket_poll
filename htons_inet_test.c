#include "stdio.h"
#include "arpa/inet.h"
#include "netinet/in.h"

int main()
{
	struct in_addr inp;
	char *str = "456";
	char **ptr = &str;
	printf("ptr = %x\n",ptr);
	printf("*ptr = %s\n",*ptr);
//	printf("**ptr = %s\n",**ptr);
	printf("htons value:%d\n",htons(**ptr));
	
//	inet_aton("192",&inp);
//	printf("inet value:%s\n",inp.s_addr);

	
	return 0; 
}
