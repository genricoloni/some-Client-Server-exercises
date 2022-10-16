#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN_REPLY 20 // Lunghezza del messaggio di risposta

int main(int argc, char* argv[]){
    //dichiarazione di variabili
    int sd, ret, len;
    struct sockaddr_in server_addr;
    char buffer[1024];

    //creo il socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    //pulizia della memoria e gestione indirizzi
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; //è IPV4
    server_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    //richiesta di connessione
    ret = connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(ret < 0){
        perror("Errore in fase di connessione: \n");
        exit(-1);
    }

    //attesa della risposta
    len = LEN_REPLY;
    ret = recv(sd, (void*)buffer, len, 0);

    if (ret < 0 ){
        perror("Errore in fase di ricezione: \n");
        exit(-1);
    }

    buffer[len] = '\0';

    printf("%s\n", buffer);

    close(sd);
}