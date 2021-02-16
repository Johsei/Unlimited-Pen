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

#define VK_D 0x44;

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
		float y, z;
		SP->ReadData(&inByte,1);
		if (inByte == 'W') // Button gedrueckt
		{
			btnPressed = true; // Entweder zu Beginn einer Datenübertragung kommt ein W (gedrueckt) oder nicht (nicht gedrueckt), zuruecksetzen erfolgt nach Einlesen von Z Daten, moegliche Fehlerquelle!
		}
		else if (inByte == 'Y') // +Y: nach links, -Y: nach rechts
		{
			if (btnPressed == true) cout << "MAUSTASTE GEDRUECKT!" << endl; // Hier why not und so

			y = ReadSerialData(SP, 'Y', &inByte); // Einlesen der vier Datenbytes
			cout << "Received Y: " << y << endl;
			
			if (y > 150 && y < 9999) Move((int)y/100, 0, 1);
			else if (y < -150 && y > -9999) Move((int)y/100, 0, -1);
		}
		else if (inByte == 'Z') // +Z: nach oben, -Z: nach unten
		{
			z = ReadSerialData(SP, 'Z', &inByte); // Einlesen der vier Datenbytes
			cout << "Received Z: " << z << endl;


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

