// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include<netinet/in.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
struct addrinfo hints, *result, *p;

//char ip[100];

memset(&hints,0,sizeof(hints));
hints.ai_family = AF_UNSPEC ; 
hints.ai_socktype=SOCK_STREAM;

  ret = getaddrinfo(name, NULL, &hints, &result);
    if (ret) {
       
        exit(1);
    }

   // struct addrinfo *p;
    char host[100];

    for (p = result; p != NULL; p = p->ai_next) {

       // if(!getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST))
        inet_ntop(p->ai_family, &(((struct sockaddr_in*)p->ai_addr)->sin_addr), host, p->ai_addrlen);
       puts(host);
       // printf("%s",host);

    }

    printf("flags:%d\n",result->ai_flags);
    printf("family:%d\n",result->ai_family);
    printf("socktype:%d\n",result->ai_socktype);
    printf("protocol:%d\n",result->ai_protocol);
    //printf("%d\n",result->);


    freeaddrinfo(result);
	
	
	// TODO: set hints

	// TODO: get addresses

	// TODO: iterate through addresses and print them

	// TODO: free allocated data
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
     
    inet_pton(AF_INET, ip, &addr.sin_addr);
    
 
     ret = getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, sizeof(host),service, sizeof(service), 0);
   		printf("service:\n");
        printf("%s\n",service );
        printf("host:\n");
         printf("%s\n",host );
         /*
int res = getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, sizeof(host),service, sizeof(service), NI_NAMEREQD);
           printf("%s\n",service );
        printf("CEVA\n");
         printf("%s\n",host );*/
	// TODO: fill in address data
 

	// TODO: get name and service

	// TODO: print name and service
}

int main(int argc, char **argv)
{
	
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
