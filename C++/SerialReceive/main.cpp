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
#include "Windows.h"
#include <CommCtrl.h>
#include <iostream>
#include <chrono>
#include "matplotlibcpp.h"

#define VK_D 0x44;

#define debug true

using namespace std;

// Von Kollege Simon übernommen
short Horizontal[20] = { 2, 3, 4, -2, -1, 3, 5, 0, 2, -1, 3,
					2, 3, 4, -2, -1, 3, 5, 0, 2 };

short Vertikal[20] = { 2, -3, 8, -2, -1, 3, 9, 0, 2, -5, 3,
					2, 3, 4, -2, -1, 2, 5, 0, 2 };

bool getData();
void Move(short Hori, short Verti, short Sensitivity);
void LeftClick();
void RightClick();
void ShowDesktop();

float ReadSerialFloat (Serial* SP, char *inByte);
float ReadSerialLong (Serial* SP, char *inByte); 
float ReadSerialLongAsChars (Serial* SP);

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // Enables one to read the current time in ms as variable "now"

	Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed
	boolean btnPressed = false;

	unsigned __int64 countMillis = 0; // Just for debug purposes
	int count = 0;
	countMillis = now;

	if (SP->IsConnected())
	{
		cout << "We're connected" << endl;
		cout << "________________" << endl;
	}

	while(SP->IsConnected())
	{
		char inByte;
		long x, y;

		SP->ReadData(&inByte,1);
		if (inByte == 'W') // Button gedrueckt
		{
			btnPressed = true; // Entweder zu Beginn einer Datenübertragung kommt ein W (gedrueckt) oder nicht (nicht gedrueckt), zuruecksetzen erfolgt nach Einlesen von Z Daten, moegliche Fehlerquelle!
		}
		else if (inByte == 'X') // OBSOLET: +Y: nach links, -Y: nach rechts
		{

			count++;
			if (count >= 1000 && debug == true)
			{
				count = 0;
				//countMillis = now - countMillis;
				now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
				cout << "----------------\nZeit nach 1000 Durchlaeufen: " << now - countMillis << "\n----------------" << endl;
				countMillis = now;	
			}

			if (btnPressed == true) cout << "MAUSTASTE GEDRUECKT!" << endl; // Hier why not und so

			x = ReadSerialLongAsChars(SP); // Einlesen der Daten
			cout << "Received X: " << x << endl;

			Move(x/5000.0, 0, 1);
			
		}
		else if (inByte == 'Y') // OBSOLET: +Z: nach oben, -Z: nach unten
		{
			y = ReadSerialLongAsChars(SP); // Einlesen der Daten
			cout << "Received Y: " << y << endl;

			Move(0, y/5000.0, 1);

			btnPressed = false; // Wird hier wieder zurueckgesetzt, da das das letzte einzulesende Datenpaket dieser Uebertragung ist
		}
	}
	return 0;
}

float ReadSerialFloat (Serial* SP, char *inByte)
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

float ReadSerialLong (Serial* SP, char *inByte)
{
	SP->ReadData(inByte,1);  //":" entsorgen
	char indata[4] = { 0 };
	if(SP->ReadData(&indata[0],1) == 0) cout << "ERROR: NO BYTE TO READ (NULL)" << endl;
	SP->ReadData(&indata[1],1);
	SP->ReadData(&indata[2],1);
	SP->ReadData(&indata[3],1);

	long g;
	memcpy(&g, &indata, sizeof(g));
	g -= 16843009; // Subtrahiert die aufseiten des Arduinos zur Vermeidung von NUL addierte Zahl

	//if (g != 0 && g < 99999 && g > -99999) cout << "Received Float: " << g << endl; // Ungültige Werte verwerfen!

	return g;
}

float ReadSerialLongAsChars (Serial* SP)
{
	char indata[16] = { 0 }; // Zahl wird immer mit Sign und 10 Stellen ausgegeben

	for (int i = 0; i < 16; ++i) {
		SP->ReadData(&indata[i],1); // Die Stellen nacheinander in das Char-Array einlesen
		if(indata[i] == '\n') break; // Wenn die Zahl aus ist raus aus der for-Schleife!
	}

	long longRead = atol(indata);
	return longRead;
}

void Move(short Hori, short Verti, short Sensitivity)
{

	INPUT inputs[1];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dx = Hori * Sensitivity;
	inputs[0].mi.dy = Verti * Sensitivity;
	inputs[0].mi.dwFlags = MOUSE_MOVED;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs))
	{
		std::cout << L"SendInput failed: 0x" << HRESULT_FROM_WIN32(GetLastError()) << "/n";
	}
}


void LeftClick()
{
	INPUT inputs[1];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs))
	{
		std::cout << L"SendInput failed: 0x" << HRESULT_FROM_WIN32(GetLastError()) << "/n";
	}
}

