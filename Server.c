#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>

#define PORT 9000
#define MAX 2000
#define ACTIVE "\033[1;32mACTIVE"
#define DE_ACTIVE "\033[1;31mDE-ACTIVE"

// Creatinng clint count global variable to check no of clients
int clientCount = 0;

// Creating client structure for each client record
struct client{
	int index;
	int socketID;
	struct sockaddr_in client_addr;
	int len;
	char status[20];
};

// Declare and initializing pthread_t type variable and struct client variable for use
struct client Client[10];
pthread_t thread[10];

void * ChattingProcess(void * ClientDetail){
	// Type casting ClientDetail to (struct clint *) type from (void *)
	struct client* clientDetail = (struct client*) ClientDetail;
	
	// Getting client index and socket id
	int index = clientDetail -> index;
	int clientSocket = clientDetail -> socketID;
	
	printf("\033[1;32m [++] Client %d connected... \033[0m\n", index+1);
	
	// sending the server Basic command Codes for CLIENT GUIDE
	char output[MAX];
	char basicCommand[MAX] = "\n\033[1;35m... [SERVER-COMMANDS-GUIDE] ...\n\n--> 'LIST'\t:- to get clients list and status\n--> 'EXIT'\t:- to end the connection\n--> 'HELP'\t:- to get command list\n\n--> '<client id> : <message>'\t:- to send message\n\n-------------------------------\033[0m\n";
	bzero(output, sizeof(output));
	strcpy(output, basicCommand);
	if(send(clientSocket, output, strlen(output), 0) < 0){
		printf("\033[1;33m [--] Can't send message... \033[0m\n");
		return NULL;
	}
	// Message processing
	while(1){
		char clientMsg[MAX];
		bool CHAT = false;
		
		// clearing the buffers
		bzero(clientMsg, sizeof(clientMsg));
		bzero(output, sizeof(output));
		
		// receving client message
		if(recv(clientSocket, clientMsg, sizeof(clientMsg), 0) < 0){
			printf("\033[1;33m [--] Couldn't receive client message... \033[0m\n");
			break;
		}
		printf("\n+++ CLIENT %d | client message : %s | client socket : %d\n",index+1, clientMsg, clientSocket);
		
		//if the message contains ':' delemeter then set CHAT = true;
		char *ck;
		ck = strstr(clientMsg,":");
		if(strlen(&ck) != 0){
			CHAT = true;
		}
		
		// user commands and actions
		if(strcmp(clientMsg, "EXIT") == 0){
			break;
		}
		else if(strcmp(clientMsg, "HELP") == 0){
			strcpy(output, basicCommand);
		}
		else if(strcmp(clientMsg, "LIST") == 0){
			int l = 0;
			if(clientCount == 1){
				l += sprintf(output + l, "\033[1;35m[res] Currently no other clients are connected...\n");
			}
			else{
				for(int i = 0; i < clientCount; i++){
					if(i != index){
						l += sprintf(output + l, "\033[1;35m[res] Client: %d | soket: %d | status : %s\n",(i+1), Client[i].socketID, Client[i].status);	// sprintf returns the no of bytes that are written in array which is held by variable l
																																								// so to append multiple sentance we need to increment output to l byte for getting that location
					}
				}
			}
			sprintf(output + l, "\033[0m\n");
		}
		else if(CHAT){
			// separating client id
			char *sep;
			sep = strtok(clientMsg, ":");
			
			// sep holds in the first token now check if the first token is contain number or not
			bool isDigit = true;
			for(int i = 0; i < strlen(sep); i++){
				if(isdigit(sep[i]) == false){
					isDigit = false;
				}
			}
			
			// Convert client id from char to int
			int id;
			
			if(isDigit){
				id = atoi(sep) - 1;
			
				// getting the message token part
				sep = strtok(NULL, ":");
				
				//if client is active then send msg otherwise send reciver client is not active to sender client
				if(strcmp(Client[id].status ,ACTIVE) == 0 && sep){
					
					//sending the message to that client 
					int l = 0;
					l = sprintf(output, "\033[1;32m[msg] From Client %d : %s", index+1, sep);
					
					// getting all the message tokens
					sep = strtok(NULL, ":");
					while(sep != NULL){
						l += sprintf(output+l, ":%s\033[0m", sep);
						sep = strtok(NULL, ":");
					}
					sprintf(output+l, "\033[0m", sep);
					
					if(send(Client[id].socketID, output, strlen(output), 0) < 0){
						printf("\033[1;33m [--] Can't send message... \033[0m\n");
						break;
					}
					
					// server response to the client for sending message successfully
					bzero(output, sizeof(output));
					sprintf(output, "\033[1;35m[res] Message sent to client %d...\033[0m\n", id+1);
					
					printf("\033[1;32m ..... Successfully send the message to client %d from client %d ..... \033[0m\n", id+1, index+1);
				}
				else{
					sprintf(output, "\033[1;31m[res] Cannot send the message since client %d is DE-ACTIVE...\033[0m\n", id+1);
				}
			}
			else{
				strcpy(output, "\033[1;31m[res] WRONG CLIENT ID...\033[0m\n");
			}
			
		}
		else{
			// wrong command response
			strcpy(output, "\033[1;31m[res] WRONG INPUT COMMAND... PLEASE TRY AGAIN WITH VALID COMMAND...\033[0m\n");
		}
		
		//sending servers response to this client
		if(send(clientSocket, output, strlen(output), 0) < 0){
			printf("\033[1;33m [--] Can't send message... \033[0m\n");
			break;
		}
		
	}
	
	// making this client status DE-ACTIVE and closing its socket
	stpcpy(clientDetail->status,DE_ACTIVE);
	close(clientSocket);
	printf("\033[1;31m \n[...] Client %d Exited...Thread id = %u \033[0m\n\n",index + 1, (unsigned int)pthread_self());
	return NULL;
}

int main(){
	// Creating the socket
	int sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc < 0){
		printf("\033[1;31m [-] Error while creating the socket... \033[0m\n");
		return -1;
	}
	printf("\033[1;36m\n [+] Socket created successfully \033[0m\n");
	
	// Creating server_addr and setting its port and IP
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Bind to the set port and IP
	if( bind(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 ){
		printf("\033[1;31m [-] Couldn't bind to the port... \033[0m\n");
		return -1;
	}
	printf("\033[1;32m [+] Done with binding... \033[0m\n");
	
	// Listen for clients
	if( listen(sock_desc,3) < 0 ){
		printf("\033[1;31m [-] Cannot Listen... \033[0m\n");
		return -1;
	}
	printf("\033[1;33m [+] Listening for incoming connections... \033[0m\n");
	
	// Accept an incoming connections
	while(clientCount < 10){
		Client[clientCount].socketID = accept(sock_desc, (struct sockaddr*)&Client[clientCount].client_addr, &Client[clientCount].len);
		Client[clientCount].index = clientCount;
		stpcpy(Client[clientCount].status,ACTIVE);
		pthread_create(&thread[clientCount], NULL, ChattingProcess, (void*)&Client[clientCount]);
		clientCount++;
	}
	
	// pthread joining which waits for a thread to terminate, detaches the thread, then returns the thread exit status
	for(int i = 0; i < clientCount; i++){
		pthread_join(thread[i], NULL);
	}
	
	printf("\n\n---DONE---\n\n");
	//closing the socket
	close(sock_desc);
	return 0;
}