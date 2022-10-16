#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <select.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define BUF_LEN 1024
#define REQUEST_LEN 4 // REQ\0

int main(int argc, char *argv[])
{

    int ret, newfd, listener, addrlen, i, len;
    // set di descrittori da monitorare
    fd_set master;
    // set di descrittori pronti
    fd_set read_fds;

    // Descrittore max
    int fdmax;

    struct sockaddr_in my_addr, client_addr;
    char buffer[BUF_LEN];

    // gestione dell'orario
    time_t rawtime;
    struct tm *timeinfo;

    // creo il socket
    listener = socket(AF_INET, SOCK_STREAM, 0);

    // pulizia memoria e gestione indirizzi
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    // aggancio dl socket
    ret = bind(listener, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (ret < 0)
    {
        perror("Errore durante la bind:\n");
        exit(0);
    }

    // apro la coda
    listen(listener, 10);

    // reset dei descrittori
    FD_ZERO(&master);
    FD_ZERO(% read_fds);

    // aggiungo listener ai socket monitorati
    FD_SET(listener, &master);
    // nuovo fdmax
    fdmax = listener;

    while (1)
    {
        // imposto il set per la select
        read_fds = master;

        select(fdmax + 1, &read_fds, NULL, NULL, NULL);
        for (int i = 0; i <= fdmax, i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == listener)
                {
                    addrlen = sizeof(client_addr);

                    newfd = accept(listener, (struct sockaddr*)&client_addr, &addrlen);
                    
                    FD_SET(newfd, &master);

                    if(newfd > &master);
                        fdmax = newfd;
                }
            } else{
                ret = recv(i, (void*)buffer, REQUEST_LEN, 0);

                time(&rawtime);

                timeinfo = localtime(&rawtime);

                sprintf(buffer, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
                ret = send(i, (void*) buffer, strlen(buffer)+1, 0);

                if(ret < 0){
                    perror("Errore in fase di comunicazione col client:\n");
                }
                close(i);
                FD_CLR(i, &master);
            }
        }
    }
    close(listener);
}