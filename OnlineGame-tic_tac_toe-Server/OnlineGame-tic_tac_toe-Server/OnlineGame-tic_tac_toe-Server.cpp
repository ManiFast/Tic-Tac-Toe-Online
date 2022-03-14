////////////////
//	   Server	  //
/////////////////

#include <iostream>
#include <WinSock2.h>

#include <string>
#include <Windows.h>
#include <ctime>

// For removing errors
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

// Users conn
SOCKET Connections[2];

//============================================================================
// No using
void ClientHandler(int index)
{
  char msg[256];

  while (true)
    recv(Connections[index], msg, sizeof(msg), NULL);
}

int switchSimvol(char *sim)
{
  if (*sim == '1')
    *sim = '2';
  else if (*sim == '2')
    *sim = '1';

  cout << "\t\t(switch simvol)" << endl;

  return *sim;
}

// Send mesg for clients
void sendAllMsg(char msg[16])
{
  send(Connections[0], msg, sizeof(msg), NULL);
  send(Connections[1], msg, sizeof(msg), NULL);
}

// For print array in grid
inline void outArr(char arr[9])
{
  cout << endl << endl;
  for (int i = 0; i < 9; i++)
  {
    cout << arr[i] << " ";
    if (i == 2)
      cout << endl;
    if (i == 5)
      cout << endl;
  }
}

// Put simvol on the certain position in grid
int inputCor(char cordinates[2], char indexes[9], char simvol[1])
{
  // Check all for xy in grid
  if (cordinates[0] == '1' && cordinates[1] == '1')
    indexes[0] = simvol[0];
  else if (cordinates[0] == '1' && cordinates[1] == '2')
    indexes[1] = simvol[0];
  else if (cordinates[0] == '1' && cordinates[1] == '3')
    indexes[2] = simvol[0];

  else if (cordinates[0] == '2' && cordinates[1] == '1')
    indexes[3] = simvol[0];
  else if (cordinates[0] == '2' && cordinates[1] == '2')
    indexes[4] = simvol[0];
  else if (cordinates[0] == '2' && cordinates[1] == '3')
    indexes[5] = simvol[0];

  else if (cordinates[0] == '3' && cordinates[1] == '1')
    indexes[6] = simvol[0];
  else if (cordinates[0] == '3' && cordinates[1] == '2')
    indexes[7] = simvol[0];
  else if (cordinates[0] == '3' && cordinates[1] == '3')
    indexes[8] = simvol[0];

  // Return not "0" but grid
  //return 0;

  for (int i = 0; i < 9; i++)
    return indexes[i];

}

int checkCor(char indexes[9], char ifWin[2])
{
  // Check only zeroes
  // On gorizontal
  if (indexes[0] == '1' && indexes[1] == '1' && indexes[2] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  else if (indexes[3] == '1' && indexes[4] == '1' && indexes[5] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  else if (indexes[6] == '1' && indexes[7] == '1' && indexes[8] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  // On vertical
  else if (indexes[0] == '1' && indexes[3] == '1' && indexes[6] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  else if (indexes[1] == '1' && indexes[4] == '1' && indexes[7] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  else if (indexes[2] == '1' && indexes[5] == '1' && indexes[8] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  // On diagonal
  else if (indexes[0] == '1' && indexes[4] == '1' && indexes[8] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }
  else if (indexes[2] == '1' && indexes[4] == '1' && indexes[6] == '1')
  {
    ifWin[0] = '1';
    ifWin[1] = '1';
  }

  // Check only crosses
  // On gorizontal
  if (indexes[0] == '2' && indexes[1] == '2' && indexes[2] == '2')
  {
    ifWin[0] = '1';
    ifWin[1] = '2';
  }
  else if (indexes[3] == '2' && indexes[4] == '2' && indexes[5] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }
  else if (indexes[6] == '2' && indexes[7] == '2' && indexes[8] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }
  // On vertical
  else if (indexes[0] == '2' && indexes[3] == '2' && indexes[6] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }
  else if (indexes[1] == '2' && indexes[4] == '2' && indexes[7] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }
  else if (indexes[2] == '2' && indexes[5] == '2' && indexes[8] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }
  // On diagonal
  else if (indexes[0] == '2' && indexes[4] == '2' && indexes[8] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }
  else if (indexes[2] == '2' && indexes[4] == '2' && indexes[6] == '2')
    {
      ifWin[0] = '1';
      ifWin[1] = '2';
    }

  // Return each element
  for (int i = 0; i < 2; i++)
  {
    return ifWin[i];
  }
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

//!==============================================================================

int main(int argc, char* argv)
{
  srand(time(NULL));

  WSADATA wsaData;
  WORD DLLLVersion = MAKEWORD(2, 2);
  if (WSAStartup(DLLLVersion, &wsaData) != 0)
  {
    cout << "Error !" << endl;
    exit(1);
  }

  SOCKADDR_IN addr;
  int sizeofaddr = sizeof(addr);
  int port = 111;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;

  SOCKET sListen;
  sListen = socket(AF_INET, SOCK_STREAM, NULL);
  bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
  listen(sListen, SOMAXCONN);

  cout << "Success ! v3" << endl;

  SOCKET newConnection;
  int countUsers = 0;

  // Create names
  const int SIZE = 16;
  char userName1[SIZE]{};   // {} - fill garbage '\0'
  char userName2[SIZE]{};
  char userNameWhoFirst[SIZE]{};

  // Catch users
  for (int i = 0; i < 2; i++)
  {
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if (newConnection == 0)
      cout << "Error connection !" << endl;
    else
    {
      Connections[i] = newConnection;
      countUsers++;

      // Save names of users    (The number after grille mean count of savees)
      if (countUsers == 1)
      {
        recv(newConnection, userName1, sizeof(userName1), NULL);			// ##1
        cout << "User " << userName1 << " successefully connected." << endl;
      }

      if (countUsers == 2)
      {
        recv(newConnection, userName2, sizeof(userName2), NULL);			// ##1
        cout << "User " << userName2 << " successefully connected." << endl;
      }

      // Multithreading (not usinng)
      //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
    }
  }

  // Send all users their names
  //sendAllMsg(userName1);		// #1
  //sendAllMsg(userName2);		// #2

  // Send first user
  send(Connections[0], userName1, sizeof(userName1), NULL);   // #1
  send(Connections[1], userName1, sizeof(userName1), NULL);   // #1

  // Send second user
  send(Connections[0], userName2, sizeof(userName2), NULL);   // #2
  send(Connections[1], userName2, sizeof(userName2), NULL);   // #2


  // Genarate who start first
  bool whoStartFirst = rand() % 2;  // 0 or 1
  char whoFirst[1];
  if (whoStartFirst == 0)
  {
    // Copy userName1 to userNameWhoFirst
    for (int i = 0; i < SIZE; i++)
    {
      if (userName1[i] == '\0')   // '\0' mean end string
        break;
      userNameWhoFirst[i] = userName1[i];
    }

    for (int i = 0; i < SIZE; i++)
    {
      if (userNameWhoFirst[i] == '\0')
        break;
      cout << userNameWhoFirst[i];
    }
    cout << " start first" << endl;
    whoFirst[0] = '0';
  }
  else if (whoStartFirst == 1)
  {
    for (int i = 0; i < SIZE; i++)
    {
      if (userName2[i] == '\0')
        break;
      userNameWhoFirst[i] = userName2[i];
    }

    for (int i = 0; i < SIZE; i++)
    {
      if (userNameWhoFirst[i] == '\0')
        break;
      cout << userNameWhoFirst[i];
    }
    cout << " start first" << endl;
    whoFirst[0] = '1';
  }
  //send(Connections[0], whoFirst, sizeof(whoFirst), NULL);   // #3
  //send(Connections[1], whoFirst, sizeof(whoFirst), NULL);   // #3

  send(Connections[0], userNameWhoFirst, sizeof(userNameWhoFirst), NULL);   // #3
  send(Connections[1], userNameWhoFirst, sizeof(userNameWhoFirst), NULL);   // #3



  // Genarate simvol
  bool simvolRand = rand() % 2;    // 0 or 1
  char simvol[1];
  if (simvolRand == 0)    // 1-O 2-X
  {
    cout << "First simvol is Circle" << endl;
    simvol[0] = '1';  // Why this 1 ? bec in 5 lines below checking if it have '0' (0 means empty)
  }
  else if (simvolRand == 1)
  {
    cout << "First simvol is Cross" << endl;
    simvol[0] = '2';
  }
  send(Connections[0], simvol, sizeof(simvol), NULL);   // #4
  send(Connections[1], simvol, sizeof(simvol), NULL);   // #4



  // Cor
  char cordinates[2];

  const int SIZEarr = 9;
  char indexes[SIZEarr];    // Grid cordinataes from array
  for (int i = 0; i < 9; i++)
    indexes[i] = '0';		// Null all

  int countMoves = 0;
  char ifWin[2]{ '0', '0' };

  // Recive codinates from Client
  // Cheking, if first started, then wait from he input
  if (whoFirst[0] == '0')   // userName1
  {
    while (true)
    {
      recv(Connections[0], cordinates, sizeof(cordinates), NULL);			// ##1
      // Input simvon on grid of array
      inputCor(cordinates, indexes, simvol);
      // Check for winner and print it, then send it
      checkCor(indexes, ifWin);
      //checkForWin(ifWin);
      //send(Connections[0], ifWin, sizeof(ifWin), NULL);   // #1
      //send(Connections[1], ifWin, sizeof(ifWin), NULL);   // #1
      // Print grid
      outArr(indexes);

      //// Send grid
      // Отправка кординат иммено тому пользователю кто первый а потом второму по очереди (если отправить сразу обоим то все встанит)
      send(Connections[0], indexes, sizeof(indexes), NULL);			// #1
      send(Connections[1], indexes, sizeof(indexes), NULL);			// #1

      switchSimvol(simvol);

      
      //Теперь наооборот ждем не с (0)первого юсера а со (1)второго (ввод  кординат)
      // Switch simvol, two times
      recv(Connections[1], cordinates, sizeof(cordinates), NULL);			// ##1
      inputCor(cordinates, indexes, simvol);
      checkCor(indexes, ifWin);
      //checkForWin(ifWin);
      //send(Connections[0], ifWin, sizeof(ifWin), NULL);   // #1
      //send(Connections[1], ifWin, sizeof(ifWin), NULL);   // #1
      outArr(indexes);

      send(Connections[0], indexes, sizeof(indexes), NULL);			// #1
      send(Connections[1], indexes, sizeof(indexes), NULL);			// #1

      switchSimvol(simvol);
    }
  }
  else if (whoFirst[0] == '1')    // userName2
  {
    while (true)
    {
      recv(Connections[1], cordinates, sizeof(cordinates), NULL);			// ##1
      inputCor(cordinates, indexes, simvol);
      checkCor(indexes, ifWin);
      //checkForWin(ifWin);
      //send(Connections[1], ifWin, sizeof(ifWin), NULL);   // #1
      //send(Connections[0], ifWin, sizeof(ifWin), NULL);   // #1
      outArr(indexes);

      send(Connections[1], indexes, sizeof(indexes), NULL);			// #1
      send(Connections[0], indexes, sizeof(indexes), NULL);			// #1

      switchSimvol(simvol);


      recv(Connections[0], cordinates, sizeof(cordinates), NULL);			// ##1
      inputCor(cordinates, indexes, simvol);
      checkCor(indexes, ifWin);
      //checkForWin(ifWin);
      //send(Connections[1], ifWin, sizeof(ifWin), NULL);   // #1
      //send(Connections[0], ifWin, sizeof(ifWin), NULL);   // #1
      outArr(indexes);

      send(Connections[1], indexes, sizeof(indexes), NULL);			// #1
      send(Connections[0], indexes, sizeof(indexes), NULL);			// #1

      switchSimvol(simvol);
    }
  }







  system("pause");
  return 0;
}