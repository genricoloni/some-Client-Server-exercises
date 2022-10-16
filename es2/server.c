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

    int sd, new_sd, len, ret;
    struct sockaddr_in my_addr, client_addr;
    char buffer[1024];

    //creo il socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    //pulizia e gestione degli indirizzi
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    //aggancio socket indirizzo
    ret = bind(sd, (struct sockaddr*)&my_addr, sizeof(my_addr));
        printf("dopo bind\n");

    //inizio l'ascolto
    ret = listen(sd, 10);
    if (ret < 0){
        perror("Errore in fase di bind: \n");
        exit(-1);
    }
        printf("dopo listen\n");


    while (1){
        len = sizeof(client_addr);

        //accettazione di una nuova connessione
        new_sd = accept(sd, (struct sockaddr*)&client_addr, (socklen_t*)&len);
            printf("dopo accept\n");

        while (1){
            
            len = MESSAGE_LEN;
            //ricevo il messaggio
            ret = recv(new_sd, (void*)buffer, len, 0);
                printf("dopo recv\n");


            if (ret < 0){
                perror("Errore durante la ricezione: \n");
                exit(-1);
            }
            if(strcmp(buffer, "bye") == 0){
                close(new_sd);
                break;
            }

            ret = send(new_sd, (void*)buffer, len, 0);
                printf("dopo send\n");

            if(ret < 0){
                perror("Errore in fase di invio: \n");
                //exit(-1);
            }
            }
    }   
}
