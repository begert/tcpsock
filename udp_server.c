#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define MAXPENDING 5
//mbe: erhoehe die buffersize, weil udp nicht streambasiert ist
#define BUFFSIZE 1500
void Die(char *mess) { perror(mess); exit(1); }
int main(int argc, char *argv[]) {
    int serversock, clientsock;
    struct sockaddr_in echoserver, echoclient;
    if (argc != 2) {
        fprintf(stderr, "USAGE: echoserver <port>\n");
        exit(1);
    }
    /* Create the UDP socket */
    //mbe: kreiere datagramm anstatt stream socket, und verwende UDP
    if ((serversock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        Die("Failed to create socket");
    }
    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver));
    /* Clear struct */
    echoserver.sin_family = AF_INET;
    /* Internet/IP */
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Incoming addr */
    echoserver.sin_port = htons(atoi(argv[1]));
    /* server port */
    /* Bind the server socket */
    if (bind(serversock, (struct sockaddr *) &echoserver,
                sizeof(echoserver)) < 0) {
        Die("Failed to bind the server socket");
    }
    //
    //mbe: kein listen() mehr bei UDP
    //
    /* Run until cancelled */
    while (1) {
        char buffer[BUFFSIZE];
        int received = -1;
        /* Receive message */
        unsigned int clientlen = sizeof(echoclient);
        //
        //mbe: kein verbindungsaufbau mit accept() bei UDP
        //
        //mbe: verwende recvfrom() anstelle von recv()
        //     hier werden alle daten aufs mal gelesen (UDP)
        if ((received = recvfrom(serversock, buffer, BUFFSIZE, 0,
                        (struct sockaddr * ) &echoclient, &clientlen)) < 0) {
            Die("Failed to receive bytes from client");
        }

        fprintf(stdout, "Client sending: %s\n",
                inet_ntoa(echoclient.sin_addr));

        /* Send back received data */
        //mbe: senden mittels sendto() anstatt send(),
        //     da keine "verbindung" herrscht (UDP) muss der 
        //     client angegeben werden
        if (sendto(serversock, buffer, received, 0,
                   (struct sockaddr * ) &echoclient, clientlen) != received) {
            Die("Failed to send bytes to client");
        }
    }
}
