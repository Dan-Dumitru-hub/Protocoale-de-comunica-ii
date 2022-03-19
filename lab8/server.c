#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

int trimite(char buffer[]){
int i=0;
char user[2];
		while(buffer[i]!=' '){
		user[i] = buffer[i];
		i++;}
user[1]='\n';
	//int i;
	sscanf(user, "%d", &i);
	return i;

}


int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;
	int n, i, ret;
	socklen_t clilen;

	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds

	if (argc < 2) {
		usage(argv[0]);
	}

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	ret = listen(sockfd, MAX_CLIENTS);
	DIE(ret < 0, "listen");

	// se adauga noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

//aici 1.2
/*
int j=0;
int ok=1;
int k=0;
*/
int v[100];
for(int i=0;i<100;i++)
v[i]=0;
//
	while (1) {
		tmp_fds = read_fds; 
		
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				if (i == sockfd) {

					// a venit o cerere de conexiune pe socketul inactiv (cel cu listen),
					// pe care serverul o accepta
					clilen = sizeof(cli_addr);
					newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
					DIE(newsockfd < 0, "accept");

					// se adauga noul socket intors de accept() la multimea descriptorilor de citire
					FD_SET(newsockfd, &read_fds);
					if (newsockfd > fdmax) { 
						fdmax = newsockfd;
					}

					printf("Noua conexiune de la %s, port %d, socket client %d\n",
							inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
					
					strcpy(buffer, "prezenti");
					send(newsockfd, buffer, strlen(buffer), 0);
						v[newsockfd]=0;
					for(int j=0;j<100;j++)
					if(v[j]>0){
					memset(buffer, 0, BUFLEN);
					sprintf(buffer, "%4d", j);
					
					send(newsockfd,buffer,strlen(buffer),0);
					memset(buffer, 0, BUFLEN);


					}
					memset(buffer, 0, BUFLEN);
					v[newsockfd]=newsockfd;
					//buffer=(char)"a intrat";
						
					for(int j=0;j<100;j++)
					if (newsockfd !=j && v[j]>0){
					strcpy(buffer, "a intrat");
					send(j, buffer, strlen(buffer), 0);
					memset(buffer, 0, BUFLEN);
					//strcpy(buffer, "a intrat");
						
					//memcpy(buffer, (char*)&newsockfd,sizeof( int)); 
					//buffer[10]=(char)newsockfd;
					sprintf(buffer, "%4d", newsockfd);
					send(j,buffer,strlen(buffer),0);
					memset(buffer, 0, BUFLEN);


					}
					
					//v[newsockfd]=newsockfd;


					/*
					if (ok)
						{j=newsockfd;
					ok=0;}
					else
					k=newsockfd;*/
				} else {
					// s-au primit date pe unul din socketii de client,
					// asa ca serverul trebuie sa le receptioneze
					memset(buffer, 0, BUFLEN);
					n = recv(i, buffer, sizeof(buffer), 0);
					///send(i, buffer, strlen(buffer), 0);        aici 1////////
					DIE(n < 0, "recv");

					if (n == 0) {
						// conexiunea s-a inchis
						printf("Socket-ul client %d a inchis conexiunea\n", i);
						v[i]=0;
					//buffer=(char)"a intrat";
						
					for(int j=0;j<100;j++)
					if (  v[j]>0){
					strcpy(buffer, "a iesit");
					send(j, buffer, strlen(buffer), 0);
					memset(buffer, 0, BUFLEN);
					//strcpy(buffer, "a intrat");
						
					//memcpy(buffer, (char*)&newsockfd,sizeof( int)); 
					//buffer[10]=(char)newsockfd;
					sprintf(buffer, "%4d", i);
					send(j,buffer,strlen(buffer),0);
					memset(buffer, 0, BUFLEN);}



						close(i);
						
						// se scoate din multimea de citire socketul inchis 
						FD_CLR(i, &read_fds);
					} else {
						printf ("S-a primit de la clientul de pe socketul %d mesajul: %s\n", i, buffer);
						//v[i]=i;
						//////1.2
						/*
						if (i==j)
						send(k, buffer, strlen(buffer), 0);
						else 
						send(j, buffer, strlen(buffer), 0);
						*/
						//////1.2
					//	printf("%d\n",trimite(buffer));
						//printf("%d\n",j);
						
						
							send(trimite(buffer), buffer, strlen(buffer), 0);
						

					//send(trimite(buffer), buffer, strlen(buffer), 0);
					//memset(buffer, 0, BUFLEN);

					}
				}
			}
		}
	}

	close(sockfd);

	return 0;
}
