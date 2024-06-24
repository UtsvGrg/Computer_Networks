#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

unsigned long long int fact[21];

void* handleClient(void *socket_desc) {
    int clientSocket = *((int *)socket_desc);
    char buffer[1024];
    int req = 50;
    
    while (req--) {
    
        bzero(buffer, 1024);
        int val_recv = recv(clientSocket, &buffer, 1024, 0);
        unsigned long long int val = strtoull(buffer, NULL, 10);
        
        // printf("Payload:%lld", val);
        if(val>20) val = 20;
        // printf(", Data Sent:%lld\n", fact[val]);
        
        bzero(buffer, 1024);   
        snprintf(buffer, 1024, "%lld", fact[val]);    
        val_recv = send(clientSocket, &buffer, 1024, 0);
    }
    return NULL;
}

int main(){

	fact[0] = 1;
	for(int i=1; i<21; i++){
		fact[i] = fact[i-1]*i;
	}

    struct sockaddr_in serverAddr, clientAddr;
    
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    if(listen(serverSocket, 10001)<0) perror("Error in listening");
    
	socklen_t addrSize = sizeof(clientAddr);

    while (1) {
    
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
        if (clientSocket < 0) {
            perror("Error on accept");
            exit(1);
        }

		// char *IP = inet_ntoa(clientAddr.sin_addr);
		// int PORT_NO = ntohs(clientAddr.sin_port);
		// printf("Client connected from  IP %s : PORT NO : %d\n", IP, PORT_NO);
		
        int *pclient = malloc(sizeof(int));
        *pclient = clientSocket;
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handleClient, (void *)pclient);		
    }
    
    close(serverSocket);
    return 0;
}
