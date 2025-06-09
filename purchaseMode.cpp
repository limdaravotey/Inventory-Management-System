#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include "data.h"
#include "purchaseMode.h"
#include "inventoryMode.h"
void loadPurchase(){
	FILE *fp = fopen("purchaseFile.txt", "r");
	if(fp == NULL) return;
	Purchase p;	NodeType *ptr = purlist;
	while(fscanf(fp, "%[^,],%d,%f,%[^,],%d,%d,%d\n", p.name, &p.qty, &p.unitprice,
	p.supplier, &p.date.dd, &p.date.mm, &p.date.yy) == 7){
		NodeType *pur = GetNode();
		if(pur == NULL){
			printf("\nError: Can't get new memory space for Node."); return;
		}
		pur->info = malloc(sizeof(Purchase));
		if (pur->info == NULL) {
	    	printf("\nError : Can't get new memory space for Info.");
			free(pur);	return;
		}
		*(Purchase *)(pur->info) = p;
		if(ptr == NULL){
			purlist = pur;
			ptr = pur;
		}else{
			ptr->next = pur;
			pur->next = NULL;
			ptr = ptr->next;
		}
	}
	fclose(fp);
}
void savePurchase(){
	NodeType *p = purlist;
	FILE *fp = fopen("purchaseFile.txt", "w");
	while(p != NULL){
		Purchase *purInfo = (Purchase *)(p->info);
		fprintf(fp, "%s,%d,%f,%s,%d,%d,%d\n", purInfo->name, purInfo->qty, purInfo->unitprice,
		purInfo->supplier, purInfo->date.dd, purInfo->date.mm, purInfo->date.yy);
		p = p->next;
	}
	fclose(fp);
}
void copyPurchase(Purchase *p1, Purchase *p2){
	strcpy(p1->name, p2->name);
	p1->qty = p2->qty;
	p1->unitprice = p2->unitprice;
	strcpy(p1->supplier, p2->supplier);
	p1->date = p2->date;
}

void inputPurchase(){
	Purchase pur;
	printAt(6,25,"Enter Purchase Product: ");		moveCursorTo(33, 25);	scanf("%s",pur.name);
	printAt(6,26,"Enter Purchase Quantity: ");		moveCursorTo(33, 26);	scanf("%d",&pur.qty);
	printAt(6,27,"Enter Purchase Unit Price: ");	moveCursorTo(33, 27);	scanf("%f",&pur.unitprice);
	printAt(6,28,"Enter Purchase Supplier: ");		moveCursorTo(33, 28);	scanf("%s",pur.supplier);
	printAt(6,29,"Enter Purchase Date : ");			moveCursorTo(33, 29);	scanf("%d %d %d",&pur.date.dd, &pur.date.mm, &pur.date.yy);
	
	NodeType *newPur;	newPur = GetNode();
	if(newPur == NULL){
		printf("\nError : Can't get new memory space for Node."); return;
	}
	newPur->info = malloc(sizeof(Purchase));
	if (newPur->info == NULL) {
    	printf("\nError : Can't get new memory space for Info.");
		free(newPur);	return;
	}
	*(Purchase *)(newPur->info) = pur;
	newPur->next = NULL;
		
	if(purlist == NULL){
		purlist = newPur;
	}
	else{
		NodeType *last = purlist;
		while(last->next != NULL){
			last = last->next;
		}
		last->next = newPur;
	}

	inputInventory(pur.name, pur.qty, pur.unitprice);
}
void showPurchase(NodeType *plist, int mode){
	//mode = 0 : show full Purchase List
	//mode = 1 : show filtered Purchase List
	char key; int start = 0;
	while(1){
		int count = listCount(plist);	system("cls");
		printAt(5,1,  "No.    Product Name            Quantity    Unit Price    Supplier                Date");
		printAt(1,2,  "----------------------------------------------------------------------------------------------------");
		if(plist == NULL)	printAt(5,4, "There is no Purchase to show right now...");
		else{
			NodeType *p = plist; for(int s=0; s<start && p!=NULL; s++) p = p->next;
			for(int i=0; i<17 && p!=NULL; i++){
				Purchase *purInfo = (Purchase *)(p->info);
				char buffer[20]; Date d = purInfo->date;
				sprintf(buffer, "%d", start+i+1);				printAt(5,4+i,buffer);
				sprintf(buffer, "%s", purInfo->name);			printAt(12,4+i,buffer);
				sprintf(buffer, "%d", purInfo->qty);			printAt(36,4+i,buffer);
				sprintf(buffer, "%.2f", purInfo->unitprice);	printAt(48,4+i,buffer);
				sprintf(buffer, "%s", purInfo->supplier);		printAt(62,4+i,buffer);
				sprintf(buffer, "%d/%d/%d", d.dd, d.mm, d.yy);	printAt(86,4+i,buffer);
				p = p->next;
			}
		}
		if(mode == 0){
			printAt(1,22, "----------------------------------------------------------------------------------------------------");
			printAt(6,23, "(B)ack    (A)dd New    (S)earch    Sort by (D)ate    (R)emove            Your Option :");
		}
		else{
			printAt(1,28, "----------------------------------------------------------------------------------------------------");
			printAt(6,29, "Press any key to go back to Purchase List...");
			getch(); break;
		}
		
		key = getArrowKey();
		if(key == 72 && start > 0) start--;
		else if(key == 80 && start < count - 1) start++;
		else if(key == 'A' || key == 'a'){
			inputPurchase(); plist = purlist;
		}
		else if(key == 'S' || key == 's'){
			char search[20];
			printAt(6,25, "Enter Product Name to Search :");
			moveCursorTo(37, 25);	scanf("%s",search);
			searchPurchase(search);
		}
		else if(key == 'D' || key == 'd'){
			while(1){
				printAt(6,25, "Enter 0 to Sort from Oldest to Newest");
				printAt(6,26, "Enter 1 to Sort from Newest to Oldest");
				int sort; moveCursorTo(63,26); scanf("%d",&sort);
				if(sort == 0)		sortPurchase(0);
				else if(sort == 1)	sortPurchase(1);
				break;
			}
		}
		else if(key == 'R' || key == 'r'){
			if(listCount(purlist) == 0){
				printAt(6,25, "There is nothing to Remove. Purchase is Empty.");
				getch();	continue;
			}
			printAt(6,25, "Enter index of Purchase Record to Remove :");
			int remove; moveCursorTo(49,25); scanf("%d",&remove);
			if((remove>0)&&(remove<=listCount(purlist))){
				removePurchase(remove);		plist = purlist;
				printAt(6,26, "Removed from Purchase Successfully! (Undo Purchase)");
				getch();
			}
			else{
				printAt(6,25, "Error : Invalid Index! Try Again.");
				getch();
			}
		}
		else if(key == 'B' || key == 'b') break;
	}
}
void searchPurchase(char name[20]){
	if(purlist == NULL) return;
	NodeType *foundlist = NULL, *foundtail = NULL, *ptr = purlist;	int found = 0;
	while(ptr != NULL){
		Purchase *purInfo = (Purchase *)(ptr->info);
		if(strcmp(name, purInfo->name)==0){
			NodeType *temp = GetNode();
			if(temp == NULL){
				printf("\nError : Can't get new memory space for Node."); return;
			}
			temp->info = malloc(sizeof(Purchase));
			if (temp->info == NULL) {
		    	printf("\nError : Can't get new memory space for Info.");
				free(temp);	return;
			}
			
			Purchase *tempInfo = (Purchase *)(temp->info);
			copyPurchase(tempInfo, purInfo);
			temp->next = NULL;
			
			if(found == 0){
				foundlist = temp;
				foundtail = foundlist;	found = 1;
			}
			else{
				foundtail->next = temp;
				foundtail = foundtail->next;
			}
		}
		ptr = ptr->next;
	}
	showPurchase(foundlist, 1);
	FreeList(foundlist);
}
void sortPurchase(int flag){
	//flag = 0 : Oldest to Newest
	//flag = 1 : Newest to Oldest
	if(purlist == NULL)				return;		//list has no data so don't sort
	else if(purlist->next == NULL)	return;		//list only has 1 data so no need to sort
	
	NodeType *p = purlist;
	NodeType *ptr = purlist;
	NodeType *mm = ptr;	//mm for min/max
	
	while(p != NULL){
		//This inner while loop find min
		while(ptr != NULL){
			Purchase *ptrInfo = (Purchase*)(ptr->info);
			Purchase *mmInfo = (Purchase*)(mm->info);
			if((flag == 0 && dateValue(ptrInfo->date) < dateValue(mmInfo->date))
			|| (flag == 1 && dateValue(ptrInfo->date) > dateValue(mmInfo->date))){
				mm = ptr;
			}
			ptr = ptr->next;
		}
		Purchase *pInfo = (Purchase*)(p->info);
		Purchase *mmInfo = (Purchase*)(mm->info);
		Purchase tempInfo;

		//Swap current node (p) with the min/max node found
		//Swap only info, the address and next linking still same
		copyPurchase(&tempInfo, pInfo);
		copyPurchase(pInfo, mmInfo);
		copyPurchase(mmInfo, &tempInfo);

		//Reset where pointers begin
		p = p->next; mm = p; ptr = p;
	}
}
void removePurchase(int purNo){
	NodeType *bef, *ptr = purlist;		int i=1;
	while(i<purNo && ptr!=NULL){
		i++;	bef = ptr;	ptr = ptr->next;
	}
	
	Purchase *purInfo = (Purchase *)(ptr->info);
	if(!removeInventory(purInfo->name, purInfo->qty, purInfo->unitprice)) goto printfail;
	
	if(ptr == purlist){
		purlist = purlist->next;
		FreeNode(ptr);
		return;
	}
	else{
		bef->next = ptr->next;
		FreeNode(ptr);
		return;
	}
	
	printfail:
	printAt(6,26, "You can't cancel Purchase of products you've already used!");
	getch();
}

/*
void fakesavelol(){
	FILE *fp = fopen("Test Purchase Record.txt", "r");
	Purchase p;	NodeType *ptr = purlist;
	while(fscanf(fp, "%[^,],%d,%f,%[^,],%d,%d,%d\n", p.name, &p.qty, &p.unitprice,
	p.supplier, &p.date.dd, &p.date.mm, &p.date.yy) == 7){
		NodeType *pur = GetNode();
		pur->info = malloc(sizeof(Purchase));
		*(Purchase *)(pur->info) = p;
		if(ptr == NULL){
			purlist = pur;
			ptr = pur;
		}else{
			ptr->next = pur;
			pur->next = NULL;
			ptr = ptr->next;
		}
		inputInventory(p.name, p.qty, p.unitprice);
	}
	fclose(fp);
}*/
