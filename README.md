# TCP-Client-Server-Socket
It's a chatting system implemented in C - Programming Language by using TCP-Socket programming. In this project multiple Client can send and receive message between each other until they are connected to the Server.
Clients can use multiple commands and command format provided by the server to communicate with the server and other actively connected clients via server. 

## Prerequisites
    1. Linux OS (if you are windows user use WSL or any Virtual Machine with Linux installed)
    2. GCC compiler
If you consider using WSL here is how you can [install WSL](https://learn.microsoft.com/en-us/windows/wsl/install) and Ubuntu or any other distributor in your windows system
    
## Installation
Start by updating the package list

```bash
  sudo apt update
```
Install GCC compiler

```bash
  sudo apt-get install gcc -y
```
Check GCC version

```bash
  gcc --version
```

## Compile & Run the code
First compile Server.c and Client.c as server and client

```bash
  gcc Server.c -o server
```
```bash
  gcc Client.c -o client
```
Then run server
```bash
  ./server
```
Then run client in differnt terminal at same location (you can run same client to multiple terminal to connect more clients with the server)
```bash
  ./client
```
## Screenshots
>RUNNING SERVER AND CLIENT

![Screenshot 2023-05-04 200954](https://user-images.githubusercontent.com/83893825/236249880-afb74a8b-eceb-473f-8cf0-836ab7e2b1b6.png)

>USE OF SOME BASIC COMMAND AND EXIT THE CLIENT

![Screenshot 2023-05-04 201035](https://user-images.githubusercontent.com/83893825/236250684-02e00097-66a8-4ce7-9453-e977598d467b.png)

>RUNNING CLIENT ON SAME TERMINAL AND ANOTHER CLIENT ON DIFFERNT TERMINAL

![Screenshot 2023-05-04 201144](https://user-images.githubusercontent.com/83893825/236251263-0c18fbbe-0af3-4b21-802d-34ffcce5826a.png)

>SENDING MESSAGE FROM CLIENT 3 TO CLIENT 2

![Screenshot 2023-05-04 201243](https://user-images.githubusercontent.com/83893825/236252706-1d371495-e1c9-4bcf-a907-d0c707860b56.png)

![Screenshot 2023-05-04 201253](https://user-images.githubusercontent.com/83893825/236253589-f4591abe-7d9f-4f5d-8983-c8342498a0b7.png)

>SOME WRONG INPUTS AND RESPONSE FROM SERVER

![Screenshot 2023-05-04 201452](https://user-images.githubusercontent.com/83893825/236254447-26b2e0ae-2576-4794-9808-4acc9d505fc8.png)

![Screenshot 2023-05-04 201506](https://user-images.githubusercontent.com/83893825/236254672-49efebd4-46a7-4980-9451-34c144555ea2.png)

>LIST COMMAND TO CHECK STATUS OF CLIENTS

![Screenshot 2023-05-04 201531](https://user-images.githubusercontent.com/83893825/236254892-3352f5d7-48f2-4ff8-874e-521693239118.png)

>CLOSING CLIENT AND THEIR STATUS

![Screenshot 2023-05-04 201545](https://user-images.githubusercontent.com/83893825/236255051-3c603366-3da3-464b-8aa3-905d4d7faa8e.png)

![Screenshot 2023-05-04 201607](https://user-images.githubusercontent.com/83893825/236255105-f804c835-190c-4393-9b24-de1bec47044a.png)
