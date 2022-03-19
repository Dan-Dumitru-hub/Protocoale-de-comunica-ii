#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include "stdio.h"
#include "string.h"
#define BUFLEN 1024


int main()
{
    BIO * bio;
    SSL * ssl;
 

    int p;

    
    char r[1024];

    /* initializare librarie */


    SSL_library_init ();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    /* TO DO initializare context */
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());


    /* incarca trust store */


    if(! SSL_CTX_load_verify_locations(ctx, "TrustStore.pem", NULL))
    {
        fprintf(stderr, "Error loading trust store\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return 0;
    }


    /* stabileste conexiune */

    bio = BIO_new_ssl_connect(ctx);

    if (bio == NULL)
    {
        perror("ssl connect:");
    }
   
    /* Seteaza flag SSL_MODE_AUTO_RETRY  */

    BIO_get_ssl(bio, & ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    /* TO DO setup conexiune */
 BIO_get_ssl(bio, &ssl);
BIO_set_conn_hostname(bio, "verisign.com:443");

    /* TO DO verifica certificat */
 if(BIO_do_connect(bio) <= 0)
    {
        perror("connect");
    }

    
    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
        perror("verifiy certificate");
    }

    /* Trimite request */


   char *request = "GET / HTTP/1.0\r\n"
                    "Host: www.verisign.com\r\n\r\n";
    int bytes;
   
    bytes = BIO_write(bio, request, strlen(request));
    if (!bytes )
    {
        if (BIO_should_retry(bio))
        {bytes = BIO_write(bio, request, strlen(request));
            
        }
        else
        {
            perror("write");
        }
    }

    /* TO DO Citeste raspuns si pregateste  output*/
  FILE *file = fopen("fisier.html", "w");
    

    int recv_count = 0;
int ok=0;
    char buf[1024];
    bytes=1;
    while(bytes>0) {
        
        memset(buf, 0, sizeof(buf));
        bytes = BIO_read(bio, buf, sizeof(buf) - 1);
        if (bytes < 0)
        {
            if (!BIO_should_retry(bio))

            {break;
                
            }

            perror("read");
        }

            if(ok)
            fwrite(buf, 1,bytes,  file);
            else ok=1;
        
    } 

    fclose(file);


    /* Inchide conexiune si elibereaza context */

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return 0;
}
