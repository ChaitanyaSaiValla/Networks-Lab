#include<iostream>
#include<stack>
#include<unistd.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

void eval_postfix(char buff[],int n)
{
    stack<int> s;
    for(int i = 0; i < n; i++)
    {
        if('0' <= buff[i] && buff[i] <= '9')
        {
            s.push(buff[i] - '0');
        }
        else
        {
            int x = s.top();
            s.pop();
            int y = s.top();
            s.pop();
            switch(buff[i]){
                case '+':
                    s.push(x + y);
                    break;
                case '/':
                    s.push(y/x);
                    break;
                case '*':
                    s.push(x * y);
                    break;
                case '-':
                    s.push(y - x);
                    break;
            }
        }
    }
    string str = to_string(s.top());
    for(int i = 0; i < str.size() ; i++)
        buff[i] = str[i];
    buff[str.size()] = '\0';
}

int main()
{
    int ser_dsc = socket(AF_INET, SOCK_STREAM, 0);
    if(ser_dsc == -1)
    {
        cout << "Socket creation failed..\n";
        return 1;
    }
    struct sockaddr_in ser_addr,client_addr;
    ser_addr.sin_family = AF_INET,
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(3001);
    if(bind(ser_dsc, (struct sockaddr *)&ser_addr,(socklen_t) sizeof(ser_addr)) < 0)
    {
        cout << "binding failed...\n";
    }
    if(listen(ser_dsc, 3) < 0)
    {
        cout << "Listening failed...\n";
        return 1;
    }
    while(1)
    {
        socklen_t sz = sizeof(client_addr);
        memset(&client_addr, 0, sz);
        int new_socket = accept(ser_dsc,(struct sockaddr*)&client_addr, &sz);
        if(new_socket < 0)
        {
            cout << "Accept failed..\n";
            continue;
        }
        while(1){
            char buff[1000],e[] = "end";
            int n = recv(new_socket, &buff, 1000, 0);
            buff[n] = '\0';
            // cout << buff << e << strcmp(buff,e) << "\n";
            if(strcmp(buff,e) == 0)
                break;
            cout << "From Client : "<< buff <<"\n";
            eval_postfix(buff, n);
            send(new_socket,&buff, strlen(buff), 0);
        }
    }
}
// g++ q1_server.cpp -o q1_server