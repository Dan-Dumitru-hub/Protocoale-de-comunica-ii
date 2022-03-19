#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"
#include "my_msg.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
  msg r;
  init(HOST,PORT);
int length;

  if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }
  printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);
 printf("filename:%s\n", r.payload+sizeof(int));

  // Send ACK:
  sprintf(r.payload,"%s", "ACK");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK sent\n");

char filename[100];
strcpy(filename,r.payload+sizeof(int));
//int length

if(recv_message(&r)<0){
  perror("Receive message");
    return -1;
}

memcpy(&length,r.payload+4,4);

sprintf(r.payload,"%s", "ACK");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK sent\n%d",length);


while(1)
{if(recv_message(&r)<0){
  perror("Receive message");
    break;}
sprintf(r.payload,"%s", "ACK");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK sent\n%s",r.payload);


}



  return 0;
}
