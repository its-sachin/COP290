#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

class Server{
    private:
    int portNum=8000;
    char message[1024];
    sockaddr_in servAddr;
    sockaddr_in clientAddr;
    socklen_t clientAddrSize;
    socklen_t servAddrSize;
    int serverSd,clientSd;
    int bindStatus=-1;
    public:

    ~Server(){
        close(clientSd);
        close(serverSd);
    }

    void setPort(int p){
        portNum=p;
    }
    void setMessage(string s){
        memset(&message, 0, sizeof(message));
        strcpy(message,s.c_str());
    }
    void innit(){
        servAddrSize=sizeof(servAddr);
        bzero((char*)&servAddr, servAddrSize);
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(portNum);    
        serverSd = socket(AF_INET, SOCK_STREAM, 0);   
        if(serverSd < 0){
            cerr << "Error establishing the server socket" << endl;
            return;
        } 
        bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,sizeof(servAddr));
        if(bindStatus < 0){
            cerr << "Error binding socket to local address" << endl;
            return;
        }  
        listen(serverSd, 1);
        clientAddrSize=sizeof(clientAddr);
        clientSd = accept(serverSd, (sockaddr *)&clientAddr, &clientAddrSize);   
        if (clientSd < 0){
            cerr << "Error accepting request from client!" << endl;
            return;
        }    
    }
    void sendMessage(string s){
        setMessage(s);
        send(clientSd, (char*)&message,strlen(message),0);
    }
    string recieveMessage(){
        memset(&message,0,sizeof(message));
        recv(clientSd,(char*)&message,sizeof(message),0);
        string s;
        strcpy(message,s.c_str());
        // cout<<s<<endl;
        return s;
    }
};