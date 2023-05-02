# TCP-Client-Server-Socket
It's a message sending application implemented in C - Programming Language by using TCP-Socket programming. In this project multiple Client can send and receive message between each other until they are connected to the Server. 

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

## Run the code
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
