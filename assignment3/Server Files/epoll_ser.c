#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <errno.h>
#include <poll.h>
#include <arpa/inet.h>

#define PORT 8080

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
	
    struct epoll_event ev, events[4010];
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listen_sd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sd, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(1);
    }

    while (1) {

        int n = epoll_wait(epfd, events, 4010, -1);
        if (n == -1) {
            perror("epoll_wait");
            exit(1);
        }

        for (int i = 0; i < n; i++) {
        
		    if (events[i].data.fd == listen_sd) {

		        int new_sd = accept(listen_sd, NULL, NULL);
		        if (new_sd < 0) {
		            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
		                break;
		            } 
		            else {
		                perror("accept");
		                exit(1);
		            }
		        }

		        ev.data.fd = new_sd;
		        ev.events = EPOLLIN | EPOLLET;

		        if (epoll_ctl(epfd, EPOLL_CTL_ADD, new_sd, &ev) == -1) {
		            perror("epoll_ctl: new_sd");
		            exit(1);
		        }
		    }
                   
            else {
            
				while(1){

					bzero(buffer, 1024);
					rc = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
					if (rc <= 0) break;
					
					long long val = atoi(buffer);

					//printf("Payload:%lld", val);
					if(val>20) val = 20;
					//printf(", Data Sent:%lld\n", fact[val]);

					sprintf(buffer,"%lld",fact[val]);

					rc = send(events[i].data.fd, buffer, sizeof(buffer), 0);
					if (rc < 0){
						perror("send() failed");
						exit(1);
					}
				}

				close(events[i].data.fd);
				events[i].data.fd = -1;
            }
        }
    }
}

