/*
 * Protocoale de comunicatii
 * Laborator 11 - E-mail
 * send_mail.c
 */

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>  
#include <unistd.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define SMTP_PORT 25
#define MAXLEN 500

/**
 * Citeste maxim maxlen octeti de pe socket-ul sockfd in
 * buffer-ul vptr. Intoarce numarul de octeti cititi.
 */
ssize_t read_line(int sockd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *buffer;

    buffer = vptr;

    for (n = 1; n < maxlen; n++) {
        if ((rc = read(sockd, &c, 1)) == 1) {
            *buffer++ = c;

            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            if (n == 1) {
                return 0;
            } else {
                break;
            }
        } else {
            if (errno == EINTR) {
                continue;
            }

            return -1;
        }
    }

    *buffer = 0;
    return n;
}

/**
 * Trimite o comanda SMTP si asteapta raspuns de la server. Comanda
 * trebuie sa fie in buffer-ul sendbuf. Sirul expected contine
 * inceputul raspunsului pe care trebuie sa-l trimita serverul
 * in caz de succes (de exemplu, codul 250). Daca raspunsul
 * semnaleaza o eroare, se iese din program.
 */
void send_command(int sockfd, const char sendbuf[], char *expected)
{
    char recvbuf[MAXLEN];
    int nbytes;
    char CRLF[2] = {13, 10};

    printf("Trimit: %s\n", sendbuf);
    write(sockfd, sendbuf, strlen(sendbuf));
    write(sockfd, CRLF, sizeof(CRLF));
  
    nbytes = read_line(sockfd, recvbuf, MAXLEN - 1);
    recvbuf[nbytes] = 0;
    printf("Am primit: %s", recvbuf);

    if (strstr(recvbuf, expected) != recvbuf) {
        printf("Am primit mesaj de eroare de la server!\n");
        exit(-1);
    }
}

int main(int argc, char **argv) {
    int sockfd;
    int port = SMTP_PORT;
    struct sockaddr_in servaddr;
    char server_ip[INET_ADDRSTRLEN];
    char sendbuf[MAXLEN]; 
    char recvbuf[MAXLEN];

    if (argc != 3) {
        printf("Utilizare: ./send_msg adresa_server nume_fisier\n");
        exit(-1);
    }

    strncpy(server_ip, argv[1], INET_ADDRSTRLEN);

    // TODO 1: creati socket-ul TCP client

 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    // TODO 2: Completati in serv_addr adresa serverului pentru bind, familia de adrese si portul rezervat pentru server
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
   // servaddr.sin_addr.s_addr =inet_addr(*(argv+2));
    servaddr.sin_port = htons(port); 

if(inet_aton(server_ip,&servaddr.sin_addr)<=0)
{
    exit(-1);
}
    // TODO 3: Asociati adresa serverului cu socketul creat folosind bind
    
    // TODO 2: completati structura sockaddr_in cu
    // portul si adresa IP ale serverului SMTP
        
    // TODO 3: conectati-va la server
if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        printf("Connect \n"); 
        return -1; 
    }
    FILE *fp;
   char buff[255];

   fp = fopen("file.txt", "r");
   

   fgets(buff, 255, (FILE*)fp);
  // printf("2: %s\n", buff );
   
  
   fclose(fp);



    // se primeste mesajul de conectare de la server
    read_line(sockfd, recvbuf, MAXLEN -1);
    printf("Am primit: %s\n", recvbuf);

    // se trimite comanda de HELO
    
    sprintf(sendbuf, "HELO localhost");
    send_command(sockfd, sendbuf, "250");


    // TODO 4: trimiteti comanda de MAIL FROM
    sprintf(sendbuf, "MAIL FROM: <dandumitru071@gmail.com>");
    send_command(sockfd, sendbuf, "250");

    // TODO 5: trimiteti comanda de RCPT TO
    sprintf(sendbuf, "RCPT TO: <dandumitru637@gmail.com>");
    send_command(sockfd, sendbuf, "250");

    // TODO 6: trimiteti comanda de DATA
    sprintf(sendbuf, "DATA");
    send_command(sockfd, sendbuf, "354");


   

    // TODO 7: trimiteti e-mail-ul (antete + corp + atasament)
    sprintf(sendbuf, "MIME-Version: 1.0\nFrom: Student Studentescu <dandumitru071@gmail.com>\nTo: Profesor PC <dandumitru637@gmail.com>\nSubject: Re: Tema\nContent-Type: multipart/mixed; boundary=abc\n\n--abc\nContent-Type: text/plain\n\nAtasez tema.\n\n--abc\nContent-Type: text/plain\nContent-Disposition: attachment; filename=file.txt\n\nThis is an attachment%s.\n\r--abc\r\n.",buff);
    send_command(sockfd, sendbuf, "250");

    // TODO 8: trimiteti comanda de QUIT
    sprintf(sendbuf, "QUIT");
    send_command(sockfd, sendbuf, "221");

    // TODO 9: inchideti socket-ul TCP client
    close(sockfd);
    /*

    sprintf(sendbuf, "HELO localhost");
    send_command(sockfd, sendbuf, "250");*//*

    sprintf(sendbuf, "AUTH LOGIN"); send_command(sockfd, sendbuf, "334");

    sprintf(sendbuf, "NDQ2MDU5NzU1NjlkY2Y="); send_command(sockfd, sendbuf, "334");


    sprintf(sendbuf, "NzQ3NGFkMjZjZDZiMzE="); send_command(sockfd, sendbuf, "235");*/

    /*

    sprintf(sendbuf, "HELO localhost");
    send_command(sockfd, sendbuf, "250");


    sprintf(sendbuf, "AUTH LOGIN");
    send_command(sockfd, sendbuf, "334");

 sprintf(sendbuf, "ZGFuZHVtaXRydTA3MUBnbWFpbC5jb20=");
    send_command(sockfd, sendbuf, "334");
    sprintf(sendbuf, "ZXB1dXlrZ3psbGRzdmVtcQ==");
    send_command(sockfd, sendbuf, "334");
    

sprintf(sendbuf, "MAIL FROM: <dan_dumitru.tipa@stud.acs.upb.ro>");
send_command(sockfd, sendbuf, "250");

    // TODO 5: trimiteti comanda de RCPT TO
    sprintf(sendbuf, "RCPT TO: <valeriu.stanciu@cti.pub.ro>");
    send_command(sockfd, sendbuf, "250");

    sprintf(sendbuf, "DATA");
    send_command(sockfd, sendbuf, "354");

    sprintf(sendbuf, "MIME-Version: 1.0\nMAIL FROM: <dan_dumitru.tipa@stud.acs.upb.ro>\nTo: valeriu.stanciu@cti.pub.ro <dandumitru637@gmail.com>\nSubject: lab11 Re: \nContent-Type: multipart/mixed; boundary=abc\n\n--abc\nContent-Type: text/plain\n\nAtasez tema.\n\n--abc\nContent-Type: text/plain\nContent-Disposition: attachment; filename=file.txt\n\nThis is an attachment.\n\r--abc\r\n.");
    send_command(sockfd, sendbuf, "250");



    sprintf(sendbuf, "QUIT");
    send_command(sockfd, sendbuf, "221");


*/
    
    return 0;
}
