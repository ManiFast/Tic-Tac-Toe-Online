
// Client //

#include <iostream>
#include <WinSock2.h>

#include <string>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

SOCKET Connection;


/*inline void outArr(char arr[9])
{
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
		if (i == 2)
			cout << endl;
		if (i == 5)
			cout << endl;
	}
}*/

void printArrSpy(char indexes[9])
{
	// Распечатка сетки со значениями
	system("cls");
	cout << endl << endl << endl;
	cout << endl << endl;
	cout << "        1        2        3    \n\n"
		<< "             |        |          \n"
		<< "  1      ";
	// Проверка есть ли в этой ячейке символ (1 или 2) 1-O 2-X
	// Проверка каждого слуячая поэтому без "else if"
	if (indexes[0] == '1')	// Проверять не с числом а как с чаром !					// 0
	{
		cout << "O";
	}
	if (indexes[0] == '2')
	{
		cout << "X";
	}
	if (indexes[0] == '0')
	{
		cout << " ";
	}
	// Если ничего нет то выводим пробел чтоб не сбились палки
	// Дальше продолжаем выводить рисунок до следующей проверки
	cout << "   |   ";
	if (indexes[1] == '1')																											// 1
	{
		cout << "O";
	}
	if (indexes[1] == '2')
	{
		cout << "X";
	}
	if (indexes[1] == '0')
	{
		cout << " ";
	}
	cout << "    |    ";
	if (indexes[2] == '1')																											// 2
	{
		cout << "O";
	}
	if (indexes[2] == '2')
	{
		cout << "X";
	}
	if (indexes[2] == '0')
	{
		cout << " ";
	}
	cout << "     \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  2      ";
	if (indexes[3] == '1')																											// 3
	{
		cout << "O";
	}
	if (indexes[3] == '2')
	{
		cout << "X";
	}
	if (indexes[3] == '0')
	{
		cout << " ";
	}
	cout << "   |   ";
	if (indexes[4] == '1')																											// 4
	{
		cout << "O";
	}
	if (indexes[4] == '2')
	{
		cout << "X";
	}
	if (indexes[4] == '0')
	{
		cout << " ";
	}
	cout << "    |   ";
	if (indexes[5] == '1')																											// 5
	{
		cout << "O";
	}
	if (indexes[5] == '2')
	{
		cout << "X";
	}
	if (indexes[5] == '0')
	{
		cout << " ";
	}
	cout << "      \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  3      ";
	if (indexes[6] == '1')																											// 6
	{
		cout << "O";
	}
	if (indexes[6] == '2')
	{
		cout << "X";
	}
	if (indexes[6] == '0')
	{
		cout << " ";
	}
	cout << "   |   ";
	if (indexes[7] == '1')																											// 7
	{
		cout << "O";
	}
	if (indexes[7] == '2')
	{
		cout << "X";
	}
	if (indexes[7] == '0')
	{
		cout << " ";
	}
	cout << "    |   ";
	if (indexes[8] == '1')																											// 8
	{
		cout << "O";
	}
	if (indexes[8] == '2')
	{
		cout << "X";
	}
	if (indexes[8] == '0')
	{
		cout << " ";
	}
	cout << "      \n"
		<< "             |        |          \n\n\n";


	// Шаблон
	/*cout << endl << endl;
	cout << "        1        2        3    \n\n"
		<< "             |        |          \n"
		<< "  1      0   |   1    |    2     \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  2      3   |   4    |    5     \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  3      6   |   7    |    8     \n"
		<< "             |        |          \n\n\n";*/

}

int main(int argc, char* argv)
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error !" << endl;
		exit(1);
	}

	cout << "Starting..." << endl;

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	int port = 111;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Error: failed connect to server." << endl;
		exit(1);
	}

	cout << "Connected !" << endl << endl;

	Sleep(0);
	system("cls");

	const int SIZE = 16;

	char userName[SIZE];
	char userName1[SIZE];
	char userName2[SIZE];

	char whoFirst[1];

	cout << "Input name (more 3 lettres): ";
	cin >> userName;

	send(Connection, userName, sizeof(userName), NULL);			// ##1

	// Input names
	recv(Connection, userName1, sizeof(userName1), NULL);		// #1
	recv(Connection, userName2, sizeof(userName2), NULL);		// #2

	system("cls");
	cout << "Users: " << userName1 << " and " << userName2 << " successfully conected.  port: " << port << endl;

	// Who first start
	recv(Connection, whoFirst, sizeof(whoFirst), NULL);			// #3
	if (whoFirst[0] == '0')
	{
		cout << userName1 << " start first" << endl;
	}
	else if (whoFirst[0] == '1')
	{
		cout << userName2 << " start first" << endl;
	}

	// Simvol
	char simvol[1];
	recv(Connection, simvol, sizeof(simvol), NULL);		// #4
	cout << "You are " << userName;
	if (simvol[0] == '1')
		cout << ". The first simvol is Circle" << endl;
	else if (simvol[0] == '2')
		cout << ". The first simvol is Cross" << endl;
	else
		cout << ". Error" << simvol[0] << endl;


	cout << endl << endl;
	cout << "        1        2        3    \n\n"
		<< "             |        |          \n"
		<< "  1          |        |          \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  2          |        |          \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  3          |        |          \n"
		<< "             |        |          \n\n\n";

	// THIS IS CHAR ! NOT INT - not 1 just '1'
	// Cor
	char cordinates[2];

	const int SIZEarr = 9;
	char indexes[SIZEarr];    // Сетка кординат из массива
	for (int i = 0; i < 9; i++)
	{
		indexes[i] = '0';		// Null all
	}

	// Сколько раз отправлять кординаты
	for (int i = 0; i < 1; i++)
	{
		//Data
		//cout << endl << whoFirst[0] << " " << userName << "\t" << userName1 << "-" << userName2 << endl;


		// Проверка кто начинает
		//		если начал 1первый то 2второй ждет (сетки)
		if (whoFirst[0] == '0')	// && userName == userName1
		{
			// Проверка имени с юзером1 по буквам
			int pass1 = 0;
			for (int i = 0; i < 4; i++)
			{
				if (userName[i] == userName1[i])
				{
					pass1++;
				}
			}
			// Если первые 2 буквы совпали то значить имя и юзер1 одинаковы
			if (pass1 >= 2)
			{
				cout << "Input coordinates (xy): ";
				// Save cordinatres
				cin >> cordinates[0];
				cin >> cordinates[1];

				// Отправка кординат
				send(Connection, cordinates, sizeof(cordinates), NULL);			// ##2
			}
		}
		else
			cout << "Waiting for the second player" << endl << endl;



		if (whoFirst[0] == '1')	// && userName == userName2
		{
			// Проверка имени с юзером2 по буквам
			int pass2 = 0;
			for (int i = 0; i < 4; i++)
			{
				if (userName[i] == userName2[i])
				{
					pass2++;
				}
			}
			// Если первые 2 буквы совпали то значить имя и юзер2 одинаковы
			if (pass2 >= 2)
			{
				cout << "Input coordinates (xy): ";
				// Save cordinatres
				cin >> cordinates[0];
				cin >> cordinates[1];

				// Отправка кординат
				send(Connection, cordinates, sizeof(cordinates), NULL);			// ##2
			}
		}
		else
			cout << "Waiting for the second player" << endl;




		// Прием сетки
		recv(Connection, indexes, sizeof(indexes), NULL);		// #5

		cout << endl;
		for (int i = 0; i < SIZEarr; i++)
		{
			cout << indexes[i] << " ";
			if (i == 2)
				cout << endl;
			if (i == 5)
				cout << endl;
		}

		// Распечатка сетки со значениями
		printArrSpy(indexes);

	}


	cout << endl << endl << endl;
	system("pause");
	return 0;
}