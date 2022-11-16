#include<iostream>
#include<unistd.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

int main()
{
    int client_dsc = socket(AF_INET, SOCK_STREAM, 0);
    if(client_dsc == -1)
    {
        cout << "Socket creation failed..\n";
        return 1;
    }
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET,
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ser_addr.sin_port = htons(3000);
    if(connect(client_dsc, (struct sockaddr*)& ser_addr, sizeof(ser_addr)) < 0)
    {
        cout<< "Connection failed..\n";
        return 1;
    }
    string s = "";
    cout << "Enter end to stop;" <<"\n";
    while(1){
        char buff[10000];
        getline(cin,s);
        if(s == "end")
            break;
        for(int i = 0; i < s.size(); i++)
            buff[i] = s[i];
        buff[s.size()] = '\0';
        send(client_dsc, &buff, strlen(buff), 0);
        recv(client_dsc, &buff, 1000, 0);
        cout << "From Server : " << buff << "\n";
    }
    close(client_dsc);
}
// g++ q2_client.cpp -o q2_client && ./q2_client