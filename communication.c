#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>

#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <wiringPi.h>

#include<stdio.h>

#include "communication.h"
#include "logging.h"

#define TW 0.15f 
#define B_CONST 2.1f
//treba zmeriat vzdialenost medzi kolama
float x = 0, y = 0, a = 0;

PI_THREAD(socket_prijem) {

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) log_msg(ERROR, "Socket did not open correctly");

    struct sockaddr_in endpoint_srv;
    memset(&endpoint_srv, 0, sizeof (struct sockaddr_in));

    endpoint_srv.sin_addr.s_addr = htonl(INADDR_ANY);
    endpoint_srv.sin_family = AF_INET;
    endpoint_srv.sin_port = htons(8888);

    if (0 > bind(fd, (struct sockaddr*) &endpoint_srv, sizeof (struct sockaddr_in)))
        log_msg(ERROR, "Bind error");


    while (1) {
        struct sockaddr_in endpoint_cli;
        memset(&endpoint_cli, 0, sizeof (struct sockaddr_in));
        endpoint_cli.sin_family = AF_INET;

        log_msg(DEBUG, "  received ");

        char buff[1000];
        socklen_t addrlen;
        int buff_len = recvfrom(fd, buff, 1000, 0, (struct sockaddr*) &endpoint_cli, &addrlen);
        if (buff_len < 0) log_msg(ERROR, "rcv from");
        buff[buff_len] = 0;

        log_msg(DEBUG, "received : %s", buff);

        int cislo;
        float v, w, p;
        if (4 != sscanf(buff, "$CTCTR,%d,%f,%f,%f*", &cislo, &v, &w, &p))
            log_msg(ERROR, "argument error");
        else {
            x = v;
            y = w;

            float v_lkolo = v + 0.5f * TW*w;
            float v_pkolo = v - 0.5f * TW*w;
            // [m/s]
            short l = (short) (v_lkolo * B_CONST), p = (short) (v_pkolo * B_CONST);

            //poslat i2cwrite(l,p);
        }

    }

}

int vytvor_prijem() {
    piThreadCreate(socket_prijem);
}

int socket_vysilani() {

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) log_msg(ERROR, "Socket did not open correctly");

    struct sockaddr_in endpoint_srv;
    memset(&endpoint_srv, 0, sizeof (struct sockaddr_in));

    endpoint_srv.sin_addr.s_addr = htonl(INADDR_ANY);
    endpoint_srv.sin_family = AF_INET;
    endpoint_srv.sin_port = htons(8889);

    if (0 > bind(fd, (struct sockaddr*) &endpoint_srv, sizeof (struct sockaddr_in)))
        log_msg(ERROR, "Bind error");


    while (1) {
        struct sockaddr_in endpoint_cli;
        memset(&endpoint_cli, 0, sizeof (struct sockaddr_in));


        if (0 == inet_aton("10.0.1.5", &endpoint_cli.sin_addr))
            log_msg(ERROR, "inet_aton error");

        endpoint_cli.sin_family = AF_INET;
        endpoint_cli.sin_port = htons(8889);


        log_msg(DEBUG, "  send ");

        char buff[256];

        memcpy(&buff[0], &x, 4);
        memcpy(&buff[4], &y, 4);
        memcpy(&buff[8], &a, 4);

        int buff_len = sendto(fd, buff, 12, 0, (struct sockaddr*) &endpoint_cli, sizeof (struct sockaddr_in));
        if (buff_len < 0) log_msg(ERROR, "rcv from");

        usleep(100000);

    }

}