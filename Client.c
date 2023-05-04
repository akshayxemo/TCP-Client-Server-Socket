#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 9000
#define MAX 2000

void * doReceving(void* socketID){
	int fd = *((int*) socketID);
	char server_message[MAX] ;
	
	while(1){
		memset(server_message,'\0',sizeof(server_message));
		
		// Receive the server's response:
		if(recv(fd, server_message, sizeof(server_message), 0) < 0){
			printf("\033[1;31m [--] Error while receiving server's msg \033[0m\n");
			return -1;
		}
		
		// printing the message
		printf("%s\n",server_message);
	}
}
int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char client_message[MAX];
    
    // Clean buffers:
	memset(client_message,'\0',sizeof(client_message));
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("\033[1;31m [-] Unable to create socket \033[0m\n");
        return -1;
    }
    
    printf("\033[1;36m\n [+] Socket created successfully... \033[0m\n");
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
    
    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("\033[1;31m [-] Unable to connect to the server \033[0m\n");
        return -1;
    }
    printf("\033[1;32m [+] Connection established... \033[0m\n");
	
	//creating a thread
	pthread_t thread;
	pthread_create(&thread, NULL, doReceving, (void*) &socket_desc);
	
	printf("\033[1;33m \n\n....... YOU CAN SEND MESSAGE TO SERVER NOW ....... \033[0m\n");
	
    while(1){
		bzero(client_message, sizeof(client_message));
		
		// Get input from the user:
		gets(client_message);
		
		if(strcmp(client_message, "EXIT")==0){
			// Send the message to server:
			if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
				printf("\033[1;31m [--] Unable to send message \033[0m\n");
				return -1;
			}
			printf("\033[1;31m \n\n[X] you have been exited...\033[0m\n");
			break;
		}
		else{
			// Send the message to server:
			if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
				printf("[--] Unable to send message\n");
				return -1;
			}
		}
    }
	
    // Close the socket:
    close(socket_desc);
	printf("\033[1;31m[X] Socket is been closed... \033[0m\n\n");
	//pthread_exit();
    return 0;
}