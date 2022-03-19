#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"
#include "my_msg.h"

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;
my_msg msg2;
//memcpy(t.payload,&msg2,sizeof(int)*strlen(payload)+1);
char * filename="fisier";
sprintf(msg2.payload,"%s",filename);
msg2.type=0;
memcpy(t.payload,&msg2,sizeof(int)+strlen(msg2.payload)+1); //punem in t.payload
t.len=sizeof(int)+strlen(msg2.payload)+1;
send_message(&t);


/*

  //Send dummy message:
  printf("[send] Sending dummy...\n");
  sprintf(t.payload,"%s", "This is a dummy.");
  t.len = strlen(t.payload)+1;
  send_message(&t);
  
  // Check response:
  if (recv_message(&t)<0){
    perror("Receive error ...");
    return -1;
  }
  else {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }
*/
if (recv_message(&t)<0){
    perror("Receive error ...");
    return -1;
  }
  else {
    printf("[send] Got reply with payload: %s\n", t.payload);}

int fd=open(filename,O_RDONLY);
int length=lseek(fd,0,SEEK_END);
lseek(fd,0,SEEK_SET);

memcpy(msg2.payload,&length,sizeof(int));
msg2.type=1;
memcpy(t.payload,&msg2,2*sizeof(int));
t.len=2*sizeof(int);
send_message(&t);

int v[5]={1,2,3,4,5};
int i=1;
int fd1=open("cv",O_RDONLY);

while(1){
lseek(fd1,i,SEEK_SET);
i++;
memcpy(msg2.payload,&length,sizeof(int));
memcpy(t.payload,&msg2,2*sizeof(int));
t.len=2*sizeof(int);
if(t.payload==0)
break;
send_message(&t);

}


  return 0;
}
