// Test.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "pch.h"
#include "Windows.h"
#include <CommCtrl.h>
#include <iostream>

#define VK_D 0x44;

int main()
{
	
}

void Move(short right, short left, short up, short down)
{
	
	INPUT inputs[1];
	ZeroMemory(inputs, sizeof(inputs));
	
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dx = right;
	inputs[0].mi.dx = left;
	inputs[0].mi.dy = up;
	inputs[0].mi.dy = down;
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

void ShowDesktop()
{
	INPUT inputs[4];
	ZeroMemory(inputs, sizeof(inputs));
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_LWIN;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_D;

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = VK_D;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_LWIN;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs))
	{
		std::cout << L"SendInput failed: 0x" << HRESULT_FROM_WIN32(GetLastError()) << "/n";
	}
}