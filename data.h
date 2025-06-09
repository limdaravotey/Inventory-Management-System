#ifndef DATA_H
#define DATA_H

typedef struct { int dd; int mm; int yy; } Date;
typedef struct { char name[20]; int qty; float unitprice; char supplier[20]; Date date; } Purchase;
typedef struct { char name[20]; int totalqty; float avgprice; } Inventory;
typedef struct { char name[20]; int qty; float unitprice; Date date; } CostRecord;
typedef struct NodeType { void *info; struct NodeType *next; } NodeType;

extern NodeType *purlist, *invlist, *costlist;
NodeType *GetNode();
void FreeNode(NodeType *p);
void FreeList(NodeType *p);
int listCount(NodeType *plist);
int dateValue(Date d);

void moveCursorTo(int x, int y);
void printAt(int x, int y, const char* text);
int getArrowKey();

#endif
