#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <stdlib.h>
#include <pthread.h>


int main(int argc , char *argv[])
{
    struct sockaddr_in ma_struct;
    struct sockaddr_in client_struct;
    int port = 8000;
    int backlog = 5;

    int nChar = 0; //number of characters
    int sock,n;


    // Create socket (slide 16)
    sock = socket(AF_INET,SOCK_STREAM,0);

    if (sock == -1) {
        printf("Erreur lors de la création du socket \n");
        return -1;
    }

    // Prepare the sockaddr_in structure (slide 15)
    ma_struct.sin_family = AF_INET;
    ma_struct.sin_port = htons (port);
    ma_struct.sin_addr.s_addr = htonl (INADDR_ANY);

    // Bind (slide 20)
    if (bind(sock, (struct sockaddr *)&ma_struct, sizeof(ma_struct)) < 0)
    {
        printf("Erreur lors de la création de la structure sockaddr \n");
        return -1;
    }

    // Listen (slide 21)
    int serv_list = listen(sock,backlog);
    if (serv_list < 0)
    {
        printf("Erreur lors de l'écoute serveur \n");
        return -1;
    }

    // Accept incoming connection (slide 22)+
    int size_client = sizeof(client_struct);

    int socket_client = accept(sock,(struct sockaddr *)&client_struct,&size_client);
    if (accept < 0)
    {
        printf("Erreur lors de l'acceptation d'un nouveau client");
        exit(EXIT_FAILURE);
    }

    char buffer[512] = "";
    // Receive message from client (slide 31 or 33)
    if ((n = recv(socket_client,buffer,511, 0))< 0)
    {
        printf("Erreur dans la reception du message");
    }

    //else if (strcmp(buffer,"q\n") != 0)

    else
    {
        buffer[n]='\0';
        printf("[SERVER] : Message recu - %s\n", buffer);
        printf("[SERVER] : Renvoi du message\n");
        n = write(socket_client,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:71\r\n\r\n<h1>Mes cours favoris</h1><hr><ol><li>RE213</li><li>RE213</li><li>RE213</li></ol>",511);
    }

    //else
    //{
        close(socket_client);
        close(sock);
        //return 0;
    //}


    // Send answer to client (slide 26 or 328)
    return 0;
}
