#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;

   // char* ip = gethostbyname("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com");
    // Ex 1.1: GET dummy from main server
    char *ip="3.8.116.10";
    char *url ="/api/v1/dummy";
    char *host = "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com";

    sockfd=open_connection(ip,8080,AF_INET,SOCK_STREAM,0);
   /*

    message=compute_get_request(host, url,NULL,NULL, NULL);
    printf("%s\n",message);

    send_to_server(sockfd,message);
   char * primit =receive_from_server(sockfd);

   printf("%s",primit);*/
   //memset(message,0,sizeof(message));

   
    // Ex 1.2: POST dummy and print response from main server



   char * content_type="application/x-www-form-urlencoded";
/*
   char **data = malloc(sizeof(char*));
    data[0] = calloc(13, sizeof(char));
    sprintf(data[0], "Hello there!");

char *message2=compute_post_request(host, url, content_type, data,1, NULL, 0);
printf("%s\n",message2);
send_to_server(sockfd,message2);
char* primit2 =receive_from_server(sockfd);

   printf("%s\n",primit2);*/

    // Ex 2: Login into main server
   char *url2 ="/api/v1/auth/login";

   
 char **data2 = malloc(sizeof(char*));
    data2[0] = calloc(100, sizeof(char));
    sprintf(data2[0], "student");
     data2[1] = calloc(10, sizeof(char));
    sprintf(data2[1], "student");
     
     char **data3 = malloc(sizeof(char*));
    data3[0] = calloc(100, sizeof(char));
sprintf(data3[0], "username=student&password=student");

char *message3=compute_post_request(host, url2, content_type, data3,1, NULL, 0);
printf("%s\n",message3);
send_to_server(sockfd,message3);
char* primit3 =receive_from_server(sockfd);

   printf("%s\n",primit3);
 char **data = malloc(1 * sizeof(char*));
    data[0] = calloc(LINELEN, sizeof(char));

    // Ex 3: GET weather key from main server
    char cookie[LINELEN];
    memset(cookie, 0, LINELEN);
    memset(data[0], 0, LINELEN);
    sprintf(data[0], "%s", cookie);


   char *start = strstr(primit3, "Set-Cookie: ");
    start += strlen("Set-Cookie: ");
    char *end = strstr(start, "\r\n");
    strncpy(cookie, start, end - start);
    
    memset(data[0], 0, LINELEN);
    sprintf(data[0], "%s", cookie);

    // Ex 3: GET weather key from main server


 char* url4="/api/v1/weather/key";
char** cookie1=malloc(sizeof(char*));
cookie1[0] = calloc(1000, sizeof(char));
sprintf(cookie1[0],"connect.sid=s%3A6I_V7nZYkCFTzzXV7fUFa0d6AZbFLffO.NxxBVG1D0GZBGGpE894vf3PgnJwyytDjB7wsuuFhYtg");


    char* message4=compute_get_request(host, url4,NULL,data, 1);
    printf("%s\n",message4);

    send_to_server(sockfd,message4);
   char * primit4 =receive_from_server(sockfd);

   printf("%s",primit4);

    // Ex 4: GET weather data from OpenWeather API
    // Ex 5: POST weather data for verification to main server
    // Ex 6: Logout from main server

    // BONUS: make the main server return "Already logged in!"

    // free the allocated data at the end!
 close_connection(sockfd);
    return 0;
}
