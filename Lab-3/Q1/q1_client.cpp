#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
int main()
{
    int socket_des;
    struct sockaddr_in ser, serv, cl;
    for (int i = 8000; i <= 8005; i++)
    {
        socket_des = socket(AF_INET, SOCK_STREAM, 0);
        ser.sin_addr.s_addr = inet_addr("127.0.0.1");
        ser.sin_family = AF_INET;
        ser.sin_port = htons(i);
        if (connect(socket_des, (struct sockaddr *)&ser, sizeof(ser)) < 0)
        {
            cout << "Free.." << i << endl;
            continue;
        }
        else
        {
            send(socket_des, "hi", 2, 0);
            cout << i << " is already listening..\n";
            close(socket_des);
        }
    }
}
