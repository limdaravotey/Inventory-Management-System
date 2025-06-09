#ifndef PURCHASE_H
#define PURCHASE_H

void loadPurchase();
void savePurchase();
void copyPurchase(Purchase *p1, Purchase *p2);

void inputPurchase();
void showPurchase(NodeType *plist, int mode);
void searchPurchase(char name[20]);
void sortPurchase(int flag);
void removePurchase(int purNo);

#endif
