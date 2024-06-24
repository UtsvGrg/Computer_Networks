#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

unsigned long long int fact[21];

void handleClient(int clientSocket) {
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
}

int main() {

	fact[0] = 1;
	for(int i=1; i<21; i++){
		fact[i] = fact[i-1]*i;
	}
	
    int clientSocket;
    pid_t pid;
    struct sockaddr_in serverAddr, clientAddr;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (serverSocket < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    if(listen(serverSocket, 10001)<0) perror("Error in listening");
    
	socklen_t addrSize = sizeof(clientAddr);
    
	int clientNum = 0;
    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &addrSize);
        if (clientSocket < 0) {
            perror("Error on accept");
            exit(1);
        }

        pid = fork();
        if (pid < 0) {
            perror("Error on fork");
            exit(1);
        }
        if (pid == 0){
            close(serverSocket);
            handleClient(clientSocket);
            exit(0);
        } 

    }
    close(serverSocket);
    return 0;
}

