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

float ReadSerialData (Serial* SP, char Key, char *inByte);

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed
	boolean btnPressed = false;

	if (SP->IsConnected())
	{
		cout << "We're connected" << endl;
		cout << "________________" << endl;
	}

	while(SP->IsConnected())
	{
		char inByte;
		SP->ReadData(&inByte,1);
		if (inByte == 'W') // Button gedrueckt
		{
			btnPressed = true; // Entweder zu Beginn einer Datenübertragung kommt ein W (gedrueckt) oder nicht (nicht gedrueckt), zuruecksetzen erfolgt nach Einlesen von Z Daten, moegliche Fehlerquelle!
		}
		else if (inByte == 'Y')
		{
			cout << "Received Y: " << ReadSerialData(SP, 'Y', &inByte) << endl;
			if (btnPressed == true) cout << "MAUSTASTE GEDRUECKT!" << endl;
			// TODO Mausbewegung, Zahlenkontrolle
		}
		else if (inByte == 'Z')
		{
			cout << "Received Z: " << ReadSerialData(SP, 'Z', &inByte) << endl;
			// TODO Mausbewegung, Zahlenkontrolle

			btnPressed = false; // Wird hier wieder zurueckgesetzt, da das das letzte einzulesende Datenpaket dieser Uebertragung ist
		}
	}
	return 0;
}

float ReadSerialData (Serial* SP, char Key, char *inByte)
{
	SP->ReadData(inByte,1);  //":" entsorgen
	char indata[4] = { 0 };
	SP->ReadData(&indata[0],1);
	SP->ReadData(&indata[1],1);
	SP->ReadData(&indata[2],1);
	SP->ReadData(&indata[3],1);

	float g;
	memcpy(&g, &indata, sizeof(g));

	//if (g != 0 && g < 99999 && g > -99999) cout << "Received Float: " << g << endl; // Ungültige Werte verwerfen!

	return g;
}

