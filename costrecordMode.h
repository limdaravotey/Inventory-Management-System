#ifndef COSTRECORD_H
#define COSTRECORD_H

void loadCostRecord();
void saveCostRecord();

void inputCostRecord(char n[20], int q, float p, Date d);
void showCostRecord(NodeType *plist, int mode);
void searchCostRecord(char name[20]);
void sortCostRecord(int flag);
void removeCostRecord(int costNo);

#endif
