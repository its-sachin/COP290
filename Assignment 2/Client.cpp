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

class Client{
    private:

    char* serverIp="127.1.0.0";
    int portNum=8000;
    char message[1024];
    struct hostent* host;
    sockaddr_in sendAddr;
    socklen_t sendAddrSize;
    int clientSd,status;
    public: 

    ~Client(){
        close(clientSd);
    }
    void setIp(string s){
        serverIp=const_cast<char*>(s.c_str());
    }
    void setPort(int p){
        portNum=p;
    }
    void setMessage(string s){
        memset(&message, 0, sizeof(message));
        strcpy(message,s.c_str());
    }
    void innit(){
        host=gethostbyname(serverIp);
        sendAddrSize=sizeof(sendAddr);
        bzero((char*)&sendAddr,sendAddrSize);
        sendAddr.sin_family=AF_INET;
        sendAddr.sin_addr.s_addr=inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        sendAddr.sin_port = htons(portNum);
        clientSd = socket(AF_INET, SOCK_STREAM, 0);
        status=connect(clientSd,(sockaddr*) &sendAddr, sendAddrSize);
        if (status<0){
            cerr<<"Error connecting to socket!"<<endl; return ;
        }
    }

    void sendMessage(string s){
        setMessage(s);
        send(clientSd,(char*)&message,strlen(message),0);
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