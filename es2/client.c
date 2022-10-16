#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MESSAGE_LEN 20 // Lunghezza del messaggio dal client

int main (int argc, char* argv[]){
    int sd, len, ret;
    struct sockaddr_in server_addr;
    char buffer[1024];

    //creo il socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    //pulizia memoria e gestione indirizzi
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    //richiesta di connessione al server
    ret = connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(ret < 0){
        perror("Errore in fase di connessione:\n");
        exit(-1);
    }

    len = MESSAGE_LEN;

    while(1){
    scanf("%[^\n]", buffer);

    ret = send(sd, (void*)buffer, len, 0);
        printf("dopo send\n");


    if (ret < 0){
        perror("Errore in fase di invio:\n");
        exit(-1);
    }

    ret = recv(sd, (void*)buffer, len, 0);

    printf("dopo recv\n");

    if (ret < 0){
        perror("Errore in fase di ricezione:\n");
        exit(-1);
    }

    printf("%s\n", buffer);

    if(strcmp(buffer, "bye\0") == 0)
        break;
    
    }
    close(sd);

    return 0;
}