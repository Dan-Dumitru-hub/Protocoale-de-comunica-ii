
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 

    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char buf [1000]={0};
    char *hello = "Hello from server"; 
       
     
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
     
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    uint32_t port = argv[1];

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT  ); 
       
    
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    


    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 

FILE *fptr;
fptr = fopen("cv1","w");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

  

FILE *fptr1;
//fptr1 = fopen(buffer,"w");
 if ((fptr1 = fopen(buffer,"r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
while ( fscanf(fptr1,"%d", &buf);)
        fprintf(fptr,"%d",buf);


    //close(server_fd) ;
    return 0; }