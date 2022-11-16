#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

FILE *fp;
char *file;

int find_size()
{
    FILE* fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    return size;
}

int main()
{
    file = "txt";
    fp = fopen(file, "r");
    int soc_dsc = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (soc_dsc == -1)
    {
        cout << "Socket Creation Failed..\n";
        return 1;
    }
    sockaddr_in server, client;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(3001);
    if (bind(soc_dsc, (sockaddr *)&server, (socklen_t)sizeof(server)) == -1)
    {
        cout << "Binding to the port Failed..\n";
        return 1;
    }

    if (listen(soc_dsc, 1) == -1)
    {
        cout << "Listening to the socket Failed..\n";
        return 1;
    }
    int size = find_size();
    size = ceil((double)size / (double)10);
    char buff[10][size + 1], buf[1024];
    int i = 0;
    while (int n = fread(buf, 1, size, fp))
    {
        buf[n] = '\0';
        strcpy(buff[i], buf);
        cout << "file : " << buf << " " << buff[i] << "\n";
        i++;
    }
    cout << "Server is listening to port : " << 3001 << "\n";
    while(1)
    {
        socklen_t len = sizeof(client);
        int new_soc = accept(soc_dsc, (sockaddr *)&client, &len);
        if (new_soc < 0)
        {
            cout << "Accepting Failed..\n";
            return 1;
        }
        char msg[100];
        int n = recv(new_soc, msg, 100, 0);
        msg[n] = '\0';
        for(int i = 0; i < 5; i++)
        {
            send(new_soc, buff[msg[i] - '0'], strlen(buff[msg[i] - '0']), 0);

            int n = recv(new_soc, buf, 1024, 0);
            buf[n] = '\0';
            cout << "message from client : " << buf << "\n";
        }

        n = recv(new_soc, msg, 100, 0);
        msg[n] = '\0';
        cout << "message form Client : " << msg << "\n";
    }
    return 0;
}