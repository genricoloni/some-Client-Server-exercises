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

    int ret, sd, new_sd, len;

    uint16_t lsmg;
    pid_t pid;
    struct sockaddr_in my_addr, client_addr;
    char buffer[BUFFER_SIZE];

    //creo socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    //pulizia memoria e gestione indirizzi
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    //aggancio del socket
    ret = bind(sd, (struct sockaddr*)&my_addr, sizeof(my_addr));
    ret = listen(sd, 10);
    if (ret < 0){
        perror("Errore in fase di bind:\n");
        exit(-1);
    }


    while (1){
        len = sizeof(client_addr);

        //accettazione di nuove connessioni
        new_sd = accept(sd, (struct sockaddr*)&client_addr, (socklen_t *)&len);

        pid = fork();
        if(pid == 0){
            //siamo nel figlio
            close(sd);
            while (1){
                //ricevo la misura del messaggio
                ret = recv(new_sd, (void*)&lsmg, sizeof(uint16_t), 0);
                
                len = ntohs(lsmg);

                //ricevo il messaggio
                ret = recv(new_sd, (void*)buffer, len, 0);

                if(ret < 0){
                    perror("Errore durante la ricezione del messaggio:\n");
                    continue;
                }
                
                
                //controllo della condizione di uscita
                if(strcmp(buffer, "bye\0") == 0){
                    break;
                }
                //reinvio il messaggio
                ret = send(new_sd, (void*)buffer, len, 0);

                if(ret < 0){
                    perror("Errore in fase di invio:\n");
                    continue;
                }
            }
            //caso in cui è stata inviata la stringa di uscita
            close(new_sd);
            //termino il processo figlio
            exit(1);
        }else{
            //processo padre
            close(new_sd);
        }
    }
}