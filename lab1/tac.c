    #include <unistd.h> /* pentru open(), exit() */
    #include <fcntl.h> /* O_RDWR */
    #include <errno.h> /* perror() */
     #include <stdio.h>
#include<stdlib.h>

    void fatal(char * mesaj_eroare)
    {
        perror(mesaj_eroare);
        //exit();
    }
     
    int main(void)
    {
        int miner_sursa, miner_destinatie;
        int copiat;
        char buf[1024];
     
        miner_sursa = open("sursa", O_RDONLY);
       
     
        if (miner_sursa < 0 )
            fatal("Nu pot deschide un fisier");
     
       // lseek(miner_sursa, 0, SEEK_END);
       
     /*
        while ((copiat = read(miner_sursa, buf, sizeof(buf)))) {

            if (copiat < 0)
                fatal("Eroare la citire");
         // printf("%ld",read(miner_sursa, buf, sizeof(buf)));

copiat = write(1, buf, copiat);

        lseek(miner_sursa, -1, SEEK_CUR);
       

        }
     */
int fd=lseek(miner_sursa,0,SEEK_END);
int n;
for(int i= fd ;i>=0;i--)
{lseek(miner_sursa,i,SEEK_SET);	
n = read(miner_sursa, buf, 1);
n = write(1, buf, 1);
}
        close(miner_sursa);
     
        return 0;
    }


