// Library von hier: https://www.computerbase.de/forum/threads/arduino-serial-kommunikation.1806400/
// Bzw primary: https://playground.arduino.cc/Interfacing/CPPWindows/

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include "Serial.cpp"
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

float HexStringToFloat(const char *s);

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed

	if (SP->IsConnected())
	{
		cout << "We're connected" << endl;
		cout << "________________" << endl;
	}

	while(SP->IsConnected())
	{

		/*
        if (SP->ReadData(incomingData,1)) // Wenn ein Zeichen eingelesen wurde gibt das 1 zurueck
		//cout << "read " << incomingData[0] << endl;
		{
			if (incomingData[0] == 'X')
			{
				//cout << "X ERKANNT!!!!!!!!!" << endl;
				while (NextFloat == false)
				if (SP->ReadData(incomingData,1) == 1) //Nur wenn wirklich 8 Zeichen eingelesen wurden, ist eine richtige Zahl angekommen
				{

					//cout << endl << "Received HEX: " << incomingData[0] << incomingData[1] << incomingData[2] << incomingData[3] << incomingData[4] << incomingData[5] << incomingData[6] << incomingData[7] << endl;
					//incomingData[10] = 0;

					//unsigned char val[8];
					//for (int i = 0; i < 8; i++) val[i] = incomingData[i];
					//float x = *(float*)val; 

					int result;
					result = strtol (incomingData,NULL,2);

					//float result = *reinterpret_cast<float*>(&incomingData[0]);
   					

					//l = strtol(&incomingData[0], (char**)NULL, 16);
					//f = (float)l;
					
					cout << "Received: " << incomingData[0] << incomingData[1] << incomingData[2] << incomingData[3] << incomingData[4] << " Int: " << result << endl;
				}
			}
			else if (incomingData[0] == 'Y')
			{
				

			}
		}
		*/

		char inByte;
		SP->ReadData(&inByte,1);
		if (inByte == 'f')
		{
			SP->ReadData(&inByte,1);  //Dispose of ":"
			char indata[4] = { 0 };
			SP->ReadData(&indata[0],1);
			SP->ReadData(&indata[1],1);
			SP->ReadData(&indata[2],1);
			SP->ReadData(&indata[3],1);

			float g;
			memcpy(&g, &indata, sizeof(g));
			cout << "Received Float: " << g << endl;
		}


			
		//cout << endl << "String: " << *str << endl;

		// for (int i = 0; i < strlen(incomingData); i++)
		// {
		// 	cout << "Char on place " << i << ": " << incomingData[i] << endl;
		// }
		// cout <<     "________________" << endl;

		


	}
	return 0;
}

