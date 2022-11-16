#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
    int sock_dsc = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sock_dsc == -1)
    {
        cout << "Socket Creation Failed..\n";
        return 1;
    }
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(3002);

    if (connect(sock_dsc, (sockaddr *)&server, (socklen_t)sizeof(server)) == -1)
    {
        cout << "Connecting to the server Failed..\n";
        return 1;
    }
    cout << "\nEnter 'end' to close the connection..\n";
    while (1)
    {
        char buff[1024], _end[] = "end";
        cout << "\nEnter String : ";
        fgets(buff, 1024, stdin);
        buff[int(strlen(buff)) - 1] = '\0';
        cout << "\nEntered string : " << buff << "\n";
        send(sock_dsc, buff, strlen(buff), 0);
        if (strcmp(buff, _end) == 0)
        {
            close(sock_dsc);
            break;
        }
        int n = recv(sock_dsc, buff, 1024, 0);
        buff[n] = '\0';
        cout << "From Server : " << buff << "\n";
    }

    return 0;
}