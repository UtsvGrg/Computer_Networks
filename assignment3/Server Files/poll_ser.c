#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

	char buffer[1024];
	
	unsigned long long int fact[21];
	fact[0] = 1;
	for(int i=1; i<21; i++){
		fact[i] = fact[i-1]*i;
	}

	int listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sd < 0){
		perror("socket() failed");
		exit(-1);
	}

	int on = 1;
	int rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on));
	if (rc < 0){
		perror("setsockopt() failed");
		exit(-1);
	}

	rc = ioctl(listen_sd, FIONBIO, (char *)&on);
	if (rc < 0){
		perror("ioctl() failed");
		exit(-1);
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
	rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
	
	if (rc < 0){
		perror("bind() failed");
		exit(-1);
	}

	rc = listen(listen_sd, 4010);
	if (rc < 0){
		perror("listen() failed");
		exit(-1);
	}
	
	struct pollfd fds[4010];
	int nfds = 1, current_size = 0;

	memset(fds, 0 , sizeof(fds));
	fds[0].fd = listen_sd;
	fds[0].events = POLLIN;

	while(1) {
	
		rc = poll(fds, nfds, -1);
		if (rc <= 0) break;

		current_size = nfds;
		for (int i = 0; i < current_size; i++){

			if(fds[i].revents == 0)
				continue;

			if (fds[i].fd == listen_sd){
				
				int new_sd = 0;
				while(new_sd!=-1){
	
					new_sd = accept(listen_sd, NULL, NULL);
					if (new_sd < 0) break;

					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				}
			}

			else{
	
				while(1){

        			bzero(buffer, 1024);
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc <= 0) break;
					
					long long val = atoi(buffer);

			        //printf("Payload:%lld", val);
					if(val>20) val = 20;
					//printf(", Data Sent:%lld\n", fact[val]);

					sprintf(buffer,"%lld",fact[val]);

					rc = send(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc < 0){
						perror("send() failed");
						exit(1);
					}
				}

				close(fds[i].fd);
				fds[i].fd = -1;

			} 
		}
	}
}


