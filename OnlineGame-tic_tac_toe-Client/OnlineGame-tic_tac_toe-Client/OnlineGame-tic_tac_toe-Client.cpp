
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

void printArrGrid(char indexes[9], char sim[1])
{
	// Print grid with values
	system("cls");
	cout << endl << endl << endl;
	cout << endl << endl;
	cout << "        1        2        3    \n\n"
		<< "             |        |          \n"
		<< "  1      ";
	// Проверка есть ли в этой ячейке символ (1 или 2) 1-O 2-X
	// Проверка каждого слуячая поэтому без "else if"
	if (indexes[0] == '1')	// Проверять не с числом а как с чаром !					// 0
		cout << "O";
	if (indexes[0] == '2')
		cout << "X";
	if (indexes[0] == '0')
		cout << " ";
	// Если ничего нет то выводим пробел чтоб не сбились палки
	// Дальше продолжаем выводить рисунок до следующей проверки и по новой
	cout << "   |   ";
	if (indexes[1] == '1')																											// 1
		cout << "O";
	if (indexes[1] == '2')
		cout << "X";
	if (indexes[1] == '0')
		cout << " ";
	cout << "    |    ";
	if (indexes[2] == '1')																											// 2
		cout << "O";
	if (indexes[2] == '2')
		cout << "X";
	if (indexes[2] == '0')
		cout << " ";
	cout << "     \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  2      ";
	if (indexes[3] == '1')																											// 3
		cout << "O";
	if (indexes[3] == '2')
		cout << "X";
	if (indexes[3] == '0')
		cout << " ";
	cout << "   |   ";
	if (indexes[4] == '1')																											// 4
		cout << "O";
	if (indexes[4] == '2')
		cout << "X";
	if (indexes[4] == '0')
		cout << " ";
	cout << "    |   ";
	if (indexes[5] == '1')																											// 5
		cout << "O";
	if (indexes[5] == '2')
		cout << "X";
	if (indexes[5] == '0')
		cout << " ";
	cout << "      \n"
		<< "             |        |          \n"
		<< "      -------------------------  \n"
		<< "             |        |          \n"
		<< "  3      ";
	if (indexes[6] == '1')																											// 6
		cout << "O";
	if (indexes[6] == '2')
		cout << "X";
	if (indexes[6] == '0')
		cout << " ";
	cout << "   |   ";
	if (indexes[7] == '1')																											// 7
		cout << "O";
	if (indexes[7] == '2')
		cout << "X";
	if (indexes[7] == '0')
		cout << " ";
	cout << "    |   ";
	if (indexes[8] == '1')																											// 8
		cout << "O";
	if (indexes[8] == '2')
		cout << "X";
	if (indexes[8] == '0')
		cout << " ";
	cout << "      \n"
		<< "             |        |          \t\t";
	if (sim[0] == '1')
		cout << "(O)";
	else if (sim[0] == '2')
		cout << "(X)";
	cout << "\n\n\n";


	// Template
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

int switchSimvol(char sim)
{
	if (sim == '1')
		sim = '2';
	else if (sim == '2')
		sim = '1';

	cout << "Switch sim" << endl;

	return sim;
}

inline void checkForWin(char ifWin[2])
{
	if (ifWin[0] == '1' && ifWin[1] == '1')
	{
		cout << "Circles are win !" << endl;
	}
	else if (ifWin[0] == '1' && ifWin[1] == '2')
	{
		cout << "Crosses are win !" << endl;
	}
}

//!=========================================================================

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

	char userName[SIZE]{};
	char userName1[SIZE]{};
	char userName2[SIZE]{};
	char userNameWhoFirst[SIZE]{};

	char whoFirst[1];

	cout << "Input name (more 3 lettres): ";
	cin >> userName;

	send(Connection, userName, sizeof(userName), NULL);			// #1

	// Input names
	recv(Connection, userName1, sizeof(userName1), NULL);		// ##1
	recv(Connection, userName2, sizeof(userName2), NULL);		// ##2

	system("cls");
	cout << "Users: " << userName1 << " and " << userName2 << " successfully conected.  port: " << port << endl;

	// Who first start
	recv(Connection, userNameWhoFirst, sizeof(userNameWhoFirst), NULL);			// ##3
	cout << userNameWhoFirst << " start first" << endl;
	/*
	if (whoFirst[0] == '0')
		cout << userName1 << " start first" << endl;
	else if (whoFirst[0] == '1')
		cout << userName2 << " start first" << endl;
	*/

	// Simvol
	char simvolFirst[1];
	recv(Connection, simvolFirst, sizeof(simvolFirst), NULL);		// ##4
	cout << "You are " << userName;
	if (simvolFirst[0] == '1')
		cout << ". The first simvolFirst is Circle" << endl;
	else if (simvolFirst[0] == '2')
		cout << ". The first simvolFirst is Cross" << endl;


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
	char indexes[SIZEarr];    // Grid cordinates of array
	for (int i = 0; i < 9; i++)
		indexes[i] = '0';		// to null all

	int countMoves = 0;
	char ifWin[2]{ '0', '0' };

	// How mach times send cordinates
	for (int i = 0; i < 1; i++)		// Keep 1 !!!
	{
		// !==> Backup <== 
		// NOT USE !
		/*
		// Checking who first, if start first, second wait (grid)
		if (whoFirst[0] == '0')	// && userName == userName1
		{
			// Проверка имени с юзером1 по буквам
			int pass1 = 0;
			for (int i = 0; i < 4; i++)
			{
				if (userName[i] == userName1[i])
					pass1++;
			}
			// Если первые 2 буквы совпали то значить имя и юзер1 одинаковы
			if (pass1 >= 2)
			{
				cout << "Input coordinates (xy): ";
				// Save cordinatres
				cin >> cordinates[0];
				cin >> cordinates[1];

				// Отправка кординат
				send(Connection, cordinates, sizeof(cordinates), NULL);			// #2
			}
		}
		else
			cout << "Waiting for the second player" << endl << endl;
		*/


		// Checking 3 letters for similarity if u not first go to else and wait cordinates
		if (userNameWhoFirst[0] == userName[0] && userNameWhoFirst[1] == userName[1] && userNameWhoFirst[2] == userName[2])
		{

			// Input cordinates
			cout << "Enter coordinates (y x): ";
			cin >> cordinates[0];
			cin >> cordinates[1];
			send(Connection, cordinates, sizeof(cordinates), NULL);		// #1
			// Recive win
			//recv(Connection, ifWin, sizeof(ifWin), NULL);		// ##1
			//checkForWin(ifWin);
			// Recive grid
			recv(Connection, indexes, sizeof(indexes), NULL);		// ##1
			/*cout << endl;
			for (int i = 0; i < SIZEarr; i++)
			{
				cout << indexes[i] << " ";
				if (i == 2)
					cout << endl;
				if (i == 5)
					cout << endl;
			}*/
			// Print array with values
			printArrGrid(indexes, simvolFirst);

			while (true)
			{
				//---- Switch action and repeat
				cout << endl << "Waiting for the second player" << endl << endl;
				recv(Connection, indexes, sizeof(indexes), NULL);		// ##1
				printArrGrid(indexes, simvolFirst);

				cout << endl << "Enter coordinates (y x): ";
				cin >> cordinates[0];
				cin >> cordinates[1];
				send(Connection, cordinates, sizeof(cordinates), NULL);		// #1
				// Recive win
				//recv(Connection, ifWin, sizeof(ifWin), NULL);			// ##1
				//checkForWin(ifWin);
				recv(Connection, indexes, sizeof(indexes), NULL);		// ##1
				printArrGrid(indexes, simvolFirst);
			}
		}
		else
			// Change to opposite value, ONLY LAST USER MUST DO THIS !
			// check if 1 == 2 and replace
			if (simvolFirst[0] == '1')
				simvolFirst[0] = '2';
			else if (simvolFirst[0] == '2')		// else if - nessasary!!!  not if
				simvolFirst[0] = '1';

		cout << "Waiting for the second player" << endl << endl;
		recv(Connection, indexes, sizeof(indexes), NULL);		// ##1
		printArrGrid(indexes, simvolFirst);

		//----
		while (true)
		{
			cout << endl << "Enter coordinates (y x): ";
			cin >> cordinates[0];
			cin >> cordinates[1];
			send(Connection, cordinates, sizeof(cordinates), NULL);		// #1
			//recv(Connection, ifWin, sizeof(ifWin), NULL);			// ##1
			//checkForWin(ifWin);
			recv(Connection, indexes, sizeof(indexes), NULL);		// ##1
			printArrGrid(indexes, simvolFirst);

			cout << "Waiting for the second player" << endl << endl;
			recv(Connection, indexes, sizeof(indexes), NULL);		// ##1
			printArrGrid(indexes, simvolFirst);
		}

	}


	cout << endl << endl << endl;
	system("pause");
	return 0;
}