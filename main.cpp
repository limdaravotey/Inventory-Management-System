#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include "data.h"
#include "purchaseMode.h"
#include "inventoryMode.h"
#include "costrecordMode.h"

void setConsoleFont(int width, int height);
void setFixedConsoleSize(int columns, int rows);

int main(){
    setConsoleFont(10, 20);			Sleep(50);
    setFixedConsoleSize(100, 30);	Sleep(50);
    loadPurchase(); loadInventory(); loadCostRecord();
	while(1){
		again:	system("cls");
		
		printAt(37,9,  "***************************");
		printAt(37,10, "*        Main Menu        *");
		printAt(37,11, "*        =========        *");
		printAt(37,12, "*                         *");
		printAt(37,13, "*   1. Purchase           *");
		printAt(37,14, "*   2. Inventory          *");
		printAt(37,15, "*   3. Cost Record        *");
		printAt(37,16, "*   4. Exit the Program   *");
		printAt(37,17, "*                         *");
		printAt(37,18, "***************************");
		printAt(34,20, "Enter Your Option from Menu : ");
		int choice;		moveCursorTo(64, 20);	scanf("%d",&choice);
		switch(choice){
			case 1 : showPurchase(purlist, 0);		break;
			case 2 : showInventory(invlist, 0);		break;
			case 3 : showCostRecord(costlist, 0);	break;
			case 4 : {
				printAt(34,22,"Exiting the Program...");
				savePurchase(); saveInventory(); saveCostRecord();
				getch(); return 0;
			}
			default: goto again;
		}
	}
	return 0;
}

void setConsoleFont(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;

    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hOut, FALSE, &cfi);

    cfi.dwFontSize.X = width;
    cfi.dwFontSize.Y = height;

    wcscpy(cfi.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}
void setFixedConsoleSize(int columns, int rows) {
    HWND consoleWindow = GetConsoleWindow();
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { columns, rows };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize = { 0, 0, columns - 1, rows - 1 };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
