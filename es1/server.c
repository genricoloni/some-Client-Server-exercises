#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Implementare un server TCP mono-processo che
//fornisce un messaggio "Hello!" ai client che si
//collegano

int main(int argrc, char* argv[]){

    int ret, sd, new_sd, len;
    struct sockaddr_in my_addr, client_addr;
    char buffer[1024];

    // creo il socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    //parte degli indirizzi
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);

    //aggancio socket-indirizzo
    ret = bind(sd, (struct sockaddr*)&my_addr, sizeof(my_addr));

    //inizio l'ascolto
    ret = listen(sd, 10);
    if(ret < 0){
        perror("Errore in fase di bind; \n");
        exit(-1);
    }

    while (1){
        len = sizeof(client_addr);

        //accettazione di nuove connessioni 
        new_sd = accept(sd, (struct sockaddr*)&client_addr, &len);

        strcpy(buffer, "Ciao cate come stai");
        len = strlen(buffer);

        //invio il messaggio
        ret = send(new_sd, (void*)buffer, len, 0);

        // gestione dell'errore
        if (ret < 0){
            perror("Errore in fase di invio: \n");
        }
        close(new_sd);
    }
}