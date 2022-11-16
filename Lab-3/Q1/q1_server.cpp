#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
int main()
{
    int socket_des, new_socket;
    struct sockaddr_in ser, client;
    socket_des = socket(AF_INET, SOCK_STREAM, 0);
    char reply[2000];
    if (socket_des < 0)
    {
        cout << "socket not created" << endl;
        return 1;
    }
    cout << "socket created" << endl;
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
    ser.sin_family = AF_INET;
    int port;
    cin >> port;
    ser.sin_port = htons(port);
    if (bind(socket_des, (struct sockaddr *)&ser, sizeof(ser)) < 0)
    {
        cout << "couldn't bind" << endl;
        return 1;
    }
    cout << "binding successful" << endl;
    listen(socket_des, 10);
    socklen_t c = sizeof(ser);
    if ((new_socket = accept(socket_des, (struct sockaddr *)&client, (socklen_t *)&c)) > 0)
    {
        cout << "Connected to " << client.sin_port << endl;
        int n = recv(new_socket, reply, 2000, 0);
        cout << reply<<endl;
    }
}
