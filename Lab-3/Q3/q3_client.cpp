#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
    int soc_dsc1 = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    int soc_dsc2 = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (soc_dsc1 == -1 || soc_dsc2 == -1)
    {
        cout << "Socket Creation Failed..\n";
        return 1;
    }
    sockaddr_in server1, server2;
    server1.sin_addr.s_addr = inet_addr("127.0.0.1");
    server1.sin_family = AF_INET;
    server1.sin_port = htons(3000);
    
    server2.sin_addr.s_addr = inet_addr("127.0.0.1");
    server2.sin_family = AF_INET;
    server2.sin_port = htons(3001);

    if(connect(soc_dsc1, (sockaddr*)&server1, (socklen_t)sizeof(server1)) == -1)
    {
        cout << "Connecting to server_1 Failed..\n";
        return 1;
    }

    cout << "Parts recevied from Server_1 : \n";
    char buff[1024],thanks[] = "THANK YOU",rec[] = "recevied..";

    for(int i = 0; i < 5; i++)
    {
        int n = recv(soc_dsc1, buff, 1024, 0);
        buff[n] = '\0';
        cout << buff << "\n";
        send(soc_dsc1, rec, strlen(rec), 0);
    }
    int n = recv(soc_dsc1, buff, 1024, 0);
    buff[n] = '\0';
    cout << "missing parts : ";
    cout << buff << "\n";
    if(connect(soc_dsc2, (sockaddr*) &server2, (socklen_t)sizeof(server2)) == -1)
    {
        cout << "Connecting to server_2 Failed..\n";
        return 1;
    }
    send(soc_dsc2, buff, strlen(buff), 0);
    cout << "Parts recevied from Server_2 : \n";

    for(int i = 0; i < 5; i++)
    {
        int n = recv(soc_dsc2, buff, 1024, 0);
        buff[n] = '\0';
        cout << buff << "\n";
        send(soc_dsc2, rec, strlen(rec), 0);
    }

    send(soc_dsc1, thanks, strlen(thanks), 0);
    send(soc_dsc2, thanks, strlen(thanks), 0);

    close(soc_dsc1);
    close(soc_dsc2);
    return 0;
}