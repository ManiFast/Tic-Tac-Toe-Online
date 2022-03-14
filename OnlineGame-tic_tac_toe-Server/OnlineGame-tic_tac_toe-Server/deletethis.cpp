int main(int argc, char* argv)
{
	srand(time(NULL));

	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error" << end;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = size(addr);
	int port = 111;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	add.sin_family = AF_INET;

	SOCKET sListen;
	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMACCONN);

	cout << "Success !" << endl;

	SOCKET newConnection;
	int countUsers = 0;
}