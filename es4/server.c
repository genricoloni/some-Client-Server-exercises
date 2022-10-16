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
int main (int argc, char* argv[]){

    int ret, newfd, listener, addrlen, i, len;
    //set di descrittori da monitorare
    fd_set master;
    //set di descrittori pronti
    fd_set read_fds;

    //Descrittore max
    int fdmax;

    struct sockaddr_in my_addr, client_addr;
    char buffer[BUF_LEN];

    //gestione dell'orario
    time_t rawtime;
    struct tm* timeinfo;

    //creo il socket
    listener = socket()

    


}