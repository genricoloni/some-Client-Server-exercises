#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){

    int ret, sd, len;
    uint16_t lmsg;
    struct sockaddr_in srv_addr;
    char buffer[BUFFER_SIZE];

    //creo il socket

    sd = socket(AF_INET, SOCK_STREAM, 0);

    //pulizia memoria e gestione indirizzi
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &srv_addr.sin_addr);

    //connessione

    ret = connect(sd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));


    if (ret < 0){
        perror("Errore in fae di connessione:\n");
        exit(-1);
    }

    while (1){
        fgets(buffer, BUFFER_SIZE, stdin);
        if(strcmp(buffer, "bye\0") == 0)
            break;

        len = strlen(buffer); //aggiungo anche il carattere di fine stringa

        lmsg = htons(len);
        

        //invio della dimensione del messaggio
        ret = send(sd, (void*)&lmsg, sizeof(uint16_t), 0);

        //invio del messaggio
        ret = send(sd, (void*)buffer, len, 0);


        //attendo la ricezione del messaggio
        //essendo un echo, conosco già la sua dimensione
        ret = recv(sd, (void*)buffer, len, 0);

        if(ret < 0){
            perror("Errore in fase di ricezione del messaggio:\n");
            exit(-1);
        }
        printf("%s", buffer);

        
    }
    close(sd);  
    return 0;
}


