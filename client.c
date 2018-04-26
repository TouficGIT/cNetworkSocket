#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>


int main(int argc , char *argv[])
{
    struct sockaddr_in ma_struct;
    struct hostent *host;
    int port = 8000;
    int socket_c,n;

    //Create socket (slide 16)
    socket_c = socket(AF_INET,SOCK_STREAM,0);

    if (socket_c == -1) {
        printf("Erreur lors de la création du socket client \n");
        return -1;
    }

    // Create struct sockaddr_in (slide 15)
    host = gethostbyname("localhost");
    if (host == 0)
    {
        printf ("Hôte inconnu \n");
        exit(EXIT_FAILURE);
    }
    bzero((char *) &ma_struct, sizeof(ma_struct));


    ma_struct.sin_family = AF_INET;
    ma_struct.sin_port = htons (port);
    bcopy((char *)host->h_addr,(char *)&ma_struct.sin_addr.s_addr,host->h_length);



    // Connect to remote server (slide 23)
    int size_addr = sizeof(ma_struct);
    int connection = connect(socket_c,(struct sockaddr *)&ma_struct,size_addr);
    if (connection < 0)
    {
        printf("Erreur lors de la tentative de connection du client \n");
        exit(EXIT_FAILURE);
    }



while (1) {
    char buffer[512] = "";
    // Send some data (slide 26 or 28)
    printf("Enter message: ");
    fgets(buffer, 511 ,stdin);
    if (strcmp(buffer,"q\n") != 0)
    {
        n = write(socket_c,buffer,strlen(buffer)-1);
        if (n < 0)
        {
            printf("Erreur dans l'écriture du message\n");
        }

        // Receive answer from server (slide 31 or 33)

        n = recv(socket_c,buffer,511, 0);
        if (n < 0)
        {
            printf("Erreur dans la lecture du message\n");
        }
        else
        {
            buffer[n]='\0';
            printf("[CLIENT] : Message du serveur recu - %s\n", buffer);
        }
    }
    else
    {
    // Close sockets (slide 17)
    close(socket_c);
    return 0;
    }
}
    return 0;
}

