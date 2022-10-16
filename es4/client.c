#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define RES_LEN     9

int main(int argc, char* argv[]){
    int ret, sd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    //comando per la richiesta al server
    char* cmd = "REQ\0";

    //creazione del socket

    sd = socket(AF_INET, SOCK_STREAM, 0);

    //pulizia memoria e gestionw indirizzi
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    //connessione al server
    ret = connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret < 0){
        perror("Errore in fase di connessione: \n");
        exit(-1);
    }

    //invio del comando
    ret = send(sd, (void*)cmd, sizeof(cmd), 0);
    if(ret < 0){
        perror("Errore in fase di invio del comando:\n");
        exit(-1);
    }

    //attesa della risposta
    ret = recv(sd, (void*)buffer, RES_LEN, 0);
    if(ret < 0){
        perror("Errore in fase di ricezione:\n");
        exit(-1);
    }

    //stampo il risultato
    printf("%s\n", buffer);

    //chiudo il socket
    close(sd);
    return 0;
}