#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 1024

int main() {

    char buffer[1024];
    unsigned long long int fact[21];
    fact[0] = 1;

    for (int i = 1; i < 21; i++) {
        fact[i] = fact[i - 1] * i;
    }

    int listen_sd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_sd < 0) {
        perror("socket() failed");
        exit(-1);
    }

    int on = 1;
    int rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

    if (rc < 0) {
        perror("setsockopt() failed");
        exit(-1);
    }

    rc = ioctl(listen_sd, FIONBIO, (char *)&on);

    if (rc < 0) {
        perror("ioctl() failed");
        exit(-1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));

    if (rc < 0) {
        perror("bind() failed");
        exit(-1);
    }

    rc = listen(listen_sd, 4010);

    if (rc < 0) {
        perror("listen() failed");
        exit(-1);
    }

    int fds[MAX_CLIENTS];
    int nfds = 0, current_size = 0;

    memset(fds, 0, sizeof(fds));
    fds[0] = listen_sd;
    nfds++;

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        int max_sd = 0;

        for (int i = 0; i < nfds; i++) {
            if (fds[i] > 0) {
                FD_SET(fds[i], &readfds);
            }

            if (fds[i] > max_sd) {
                max_sd = fds[i];
            }
        }

        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(listen_sd, &readfds)) {
            int new_sd = accept(listen_sd, NULL, NULL);

            if (new_sd < 0) {
                perror("accept() failed");
                exit(1);
            }

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (fds[i] == 0) {
                    fds[i] = new_sd;
                    nfds++;
                    break;
                }
            }
        }

        for (int i = 1; i < nfds; i++) {
            if (FD_ISSET(fds[i], &readfds)) {
                bzero(buffer, 1024);
                
                rc = recv(fds[i], buffer, sizeof(buffer), 0);

                if (rc <= 0) {
                    close(fds[i]);
                    fds[i] = 0;
                    continue;
                }

                long long val = atoi(buffer);
                
                //printf("Payload:%lld", val);
                if (val > 20) val = 20;
                //printf(", Data Sent:%lld\n", fact[val]);

                sprintf(buffer, "%lld", fact[val]);

                rc = send(fds[i], buffer, sizeof(buffer), 0);

                if (rc < 0) {
                    perror("send() failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    return 0;
}

