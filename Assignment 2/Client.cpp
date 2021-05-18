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

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    public: 

    void innit(){
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return ;
        }
    
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        
        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
        {
            printf("\nInvalid address/ Address not supported \n");
            return ;
        }
    
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return ;
        }
    }

    void sendMessage(const char* s){
        send(sock , s , strlen(s)*sizeof(char) , 0 );
        cout<<"sendc: " <<s<<endl;
    }

    string recieveMessage(){
        valread = recv( sock , buffer, 1024,0);
        string s(buffer);
        // strcpy(buffer,s.c_str());
        cout<<"recievec: "<<s<<endl;
        return s.substr(0,valread);
    }


};