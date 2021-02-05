// Library von hier: https://www.computerbase.de/forum/threads/arduino-serial-kommunikation.1806400/
// Bzw primary: https://playground.arduino.cc/Interfacing/CPPWindows/

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include "Serial.cpp"
#include <string>

using namespace std;

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed

	if (SP->IsConnected())
	{
		cout << "We're connected" << endl;
		cout << "________________" << endl;
	}

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	int dataLength = 1;
	int readResult = 0;

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);
		printf("Bytes read: (0 means no data available) %i\n",readResult);
        incomingData[readResult] = 0;

        if (strlen(incomingData) > 0)
		{
			string str(incomingData);
			cout << endl << "String: " << str << endl;

			// for (int i = 0; i < strlen(incomingData); i++)
			// {
			// 	cout << "Char on place " << i << ": " << incomingData[i] << endl;
			// }
			// cout <<     "________________" << endl;
		}
    
		//Sleep(100);
	}
	return 0;
}