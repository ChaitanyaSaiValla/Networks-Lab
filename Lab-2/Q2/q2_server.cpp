#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
using namespace std;

void rev(char buff[],int n)
{
    for(int i = 0; i < n/2; i++)
    {
        swap(buff[i], buff[n - i - 1]);
    }
}

int main()
{
    int cnt = 0;
    int fd[2];
    if(pipe(fd) == -1)
    {
        cout << "Piping failed\n";
        return 1;
    }
    write(fd[1], &cnt, 4);

    int ser_dsc = socket(AF_INET, SOCK_STREAM, 0);
    if(ser_dsc == -1)
    {
        cout << "Socket creation failed..\n";
        return 1;
    }
    struct sockaddr_in ser_addr,client_addr;
    ser_addr.sin_family = AF_INET,
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(3000);
    if(bind(ser_dsc, (struct sockaddr *)&ser_addr,(socklen_t) sizeof(ser_addr)) < 0)
    {
        cout << "binding failed...\n";
        return 1;

    }
    if(listen(ser_dsc, 3) < 0)
    {
        cout << "Listening failed...\n";
        return 1;
    }
    while(1)
    {
        do{ 
            read(fd[0], &cnt, 4);
            write(fd[1], &cnt, 4);
        }while(cnt >= 5);
        socklen_t sz = sizeof(client_addr);
        int new_socket = accept(ser_dsc,(struct sockaddr*)&client_addr, &sz);
    
        if(new_socket < 0)
        {
            cout << "Accept failed..\n";
            continue;
        }
        read(fd[0], &cnt, 4);
        cnt++;
        cout << "clients :" << cnt << "\n";
        write(fd[1], &cnt, 4);

        int pid;
        if((pid = fork()) == 0)
        {
            // cout << getppid() << "\n\n";
            while(1){
                char buff[10000];
                char e[] = "end";
                int n = recv(new_socket,buff, 10000, 0);
                buff[n] = '\0';
                if(strcmp(buff,e) == 0)
                    break;
                cout << buff << "\n";
                rev(buff, strlen(buff));
                send(new_socket, &buff, strlen(buff), 0);
            }  
            int cnt2;
            read(fd[0],&cnt2, 4);
            cnt2--;
            write(fd[1], &cnt2, 4);
            close(new_socket);
            return 0;
        }
    }
}
// g++ q2_server.cpp -o q2_server