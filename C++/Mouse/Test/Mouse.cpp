#include "pch.h"
#include "Windows.h"
#include <CommCtrl.h>
#include <iostream>

#define VK_D 0x44;

short Horizontal[20] = { 2, 3, 4, -2, -1, 3, 5, 0, 2, -1, 3,
					2, 3, 4, -2, -1, 3, 5, 0, 2 };

short Vertikal[20] = { 2, -3, 8, -2, -1, 3, 9, 0, 2, -5, 3,
					2, 3, 4, -2, -1, 2, 5, 0, 2 };

bool getData();
void Move(short Hori, short Verti, short Sensitivity);
void LeftClick();
void RightClick();
void ShowDesktop();

int main()
{
	int i = 0;
	do
	{
		if (getData())
		{
			Move(Horizontal[i], Vertikal[i], 15); 
		}

		RightClick();
		i++;

		if (i > sizeof(Horizontal) / sizeof(short))
		{
			i = 0;
		}
	} while (true);
	
}

bool getData()
{
	
	

	return true;
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
void RightClick()
{
	INPUT inputs[1];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

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