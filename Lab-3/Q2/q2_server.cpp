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
    sockaddr_in server, client;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(3002);

    if (bind(sock_dsc, (sockaddr *)&server, (socklen_t)sizeof(server)) == -1)
    {
        cout << "Binding to the port Failed..\n";
        return 1;
    }

    if (listen(sock_dsc, 1) == -1)
    {
        cout << "Listening to the socket Failed..\n";
        return 1;
    }
    cout << "Server is listening to port : " << 3002 << "\n";
    while (1)
    {
        int len = sizeof(client);
        int new_soc = accept(sock_dsc, (sockaddr *)&client, (socklen_t *)&len);
        if (new_soc < 0)
        {
            cout << "Accepting Failed..\n";
            return 1;
        }
        while (1)
        {

            char buff[1024], _end[] = "end";
            int n = recv(new_soc, buff, 1024, 0);
            buff[n] = '\0';
            cout << "From client : " << buff << "\n";
            if (strcmp(buff, _end) == 0)
            {
                cout << "Closing the connection with client " << ntohs(client.sin_port) << "\n";
                close(new_soc);
                break;
            }
            send(new_soc, buff, strlen(buff), 0);
        }
    }

    return 0;
}