#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include "data.h"

//Global Variables :
NodeType *purlist = NULL;
NodeType *invlist = NULL;
NodeType *costlist = NULL;

//Linked List Components :
NodeType *GetNode() {
    NodeType *newNode = (NodeType *)malloc(sizeof(NodeType));
    if (newNode != NULL) {
        newNode->next = NULL;
    }
    return newNode;
}
void FreeNode(NodeType *p){
	free(p->info);	free(p);
}
void FreeList(NodeType *p){
	NodeType *ptr;
	while(p != NULL){
		ptr = p->next;
		free(p->info);	free(p);
		p = ptr;
	}
}
int listCount(NodeType *plist){
	NodeType *p = plist; int i = 0;
	while(p != NULL){
		i++;	p = p->next;
	}	return i;
}
int dateValue(Date d){
	int value = d.yy*10000 + d.mm*100 + d.dd;
	return value;
}

//Other Utilities :
void moveCursorTo(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printAt(int x, int y, const char* text) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("%s", text);
}
int getArrowKey() {
	int first = getch();
	if (first == 224 || first == 0) {
		int second = getch();
		return second;
	}
	return first;
}
