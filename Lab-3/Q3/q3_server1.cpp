#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

FILE *fp;
char file[10] = "txt";

int find_size()
{
    FILE *fp;
    fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    return size;
}

int main()
{
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
    server.sin_port = htons(3000);
    if (bind(soc_dsc, (sockaddr *)&server, (socklen_t)sizeof(server)) == -1)
    {
        cout << "Binding to the port Failed..\n";
        return 1;
    }
    int size = find_size();
    cout << size << "\n";
    size = ceil((double)size / (double)10);
    cout << size << "\n";
    char buff[10][size + 1], buf[1024];
    int i = 0;
    while (int n = fread(buf, 1, size, fp))
    {
        buf[n] = '\0';
        strcpy(buff[i], buf);
        cout << "file : " << buf << " " << buff[i] << "\n";
        i++;
    }
    if (listen(soc_dsc, 1) == -1)
    {
        cout << "Listening to the socket Failed..\n";
        return 1;
    }
    cout << "Server is listening to port : " << 3000 << "\n";

    while (1)
    {
        socklen_t len = sizeof(client);
        int new_soc = accept(soc_dsc, (sockaddr *)&client, &len);
        if (new_soc < 0)
        {
            cout << "Accepting Failed..\n";
            return 1;
        }
        int arr[10];
        for (int i = 0; i < 10; i++)
        {
            arr[i] = i;
        }
        random_shuffle(arr, arr + 10);
        for (int i = 0; i < 5; i++)
        {
            send(new_soc, buff[arr[i]], strlen(buff[arr[i]]), 0);
            int n = recv(new_soc, buf, 1024, 0);
            buf[n] = '\0';
            cout << "message from client : " << buf << "\n";
        }

        char missed[6];
        for (int i = 5; i < 10; i++)
        {
            missed[i - 5] = char(arr[i] + '0');
        }
        missed[5] = '\0';
        send(new_soc, missed, strlen(missed), 0);

        int n = recv(new_soc, buf, 1024, 0);
        buf[n] = '\0';
        cout << "message from client : " << buf << "\n";
        close(new_soc);
    }

    return 0;
}