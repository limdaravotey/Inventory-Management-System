#ifndef INVENTORY_H
#define INVENTORY_H

void loadInventory();
void saveInventory();
void copyInventory(Inventory *p1, Inventory *p2);

void inputInventory(char n[20], int q, float p);
void showInventory(NodeType *plist, int mode);
void searchInventory(char n[20]);
void sortInventory(int flag);
bool removeInventory(char n[20], int q, float p);

#endif
