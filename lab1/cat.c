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
     
        lseek(miner_sursa, 0, SEEK_SET);
       
     
        while ((copiat = read(miner_sursa, buf, sizeof(buf)))) {
            if (copiat < 0)
                fatal("Eroare la citire");
         // printf("%ld",read(miner_sursa, buf, sizeof(buf)));

copiat = write(1, buf, copiat);
        }
     
        close(miner_sursa);
     
        return 0;
    }


