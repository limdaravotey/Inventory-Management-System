#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "data.h"
#include "inventoryMode.h"
#include "costrecordMode.h"
void loadCostRecord(){
	FILE *fp = fopen("costrecordFile.txt", "r");
	if(fp == NULL) return;
	CostRecord p;	NodeType *ptr = costlist;
	if(ptr != NULL) while(ptr->next != NULL) ptr = ptr->next;
	while(fscanf(fp, "%[^,],%d,%f,%d,%d,%d\n", p.name, &p.qty, &p.unitprice, &p.date.dd, &p.date.mm, &p.date.yy) == 6){
		NodeType *cost = GetNode();
		if(cost == NULL){
			printf("\nError: Can't get new memory space for Node."); return;
		}
		cost->info = malloc(sizeof(CostRecord));
		if (cost->info == NULL) {
	    	printf("Error : Can't get new memory space for Info.");
			free(cost);	return;
		}
		*(CostRecord *)(cost->info) = p;
		if(ptr == NULL){
			costlist = cost;
			ptr = cost;
		}else{
			ptr->next = cost;
			cost->next = NULL;
			ptr = ptr->next;
		}
	}
	fclose(fp);
}
void saveCostRecord(){
	FILE *fp = fopen("costrecordFile.txt", "w");
	NodeType *p = costlist;
	while(p != NULL){
		CostRecord *costInfo = (CostRecord *)(p->info);
		fprintf(fp, "%s,%d,%f,%d,%d,%d\n", costInfo->name, costInfo->qty,
		costInfo->unitprice, costInfo->date.dd, costInfo->date.mm, costInfo->date.yy);
		p = p->next;
	}
	fclose(fp);
}
void copyCostRecord(CostRecord *p1, CostRecord *p2){
	strcpy(p1->name, p2->name);
	p1->qty = p2->qty;
	p1->unitprice = p2->unitprice;
	p1->date = p2->date;
}

void inputCostRecord(char n[20], int q, float p, Date d){
	CostRecord cost;
	strcpy(cost.name, n);
	cost.qty = q;
	cost.unitprice = p;
	cost.date = d;
	
	NodeType *newCost;	newCost = GetNode();
	if(newCost == NULL){
		printf("\nError: Can't get new memory space for Node."); return;
	}
	newCost->info = malloc(sizeof(CostRecord));
	if (newCost->info == NULL) {
    	printf("\nError : Can't get new memory space for Info.");
		free(newCost);	return;
	}
	*(CostRecord *)(newCost->info) = cost;
	newCost->next = NULL;
		
	if(costlist == NULL){
		costlist = newCost;
	}
	else{
		NodeType *last = costlist;
		while(last->next != NULL){
			last = last->next;
		}
		last->next = newCost;
	}
}
void showCostRecord(NodeType *plist, int mode){
	//mode = 0 : show full Cost Record List
	//mode = 1 : show filtered Cost Record List
	char key; int start = 0;
	while(1){
		int count = listCount(plist);	system("cls");
		printAt(11,1,  "No.       Product Name               Quantity       Unit Price       Date");
		printAt(1,2,  "----------------------------------------------------------------------------------------------------");
		if(plist == NULL)	printAt(11,4, "There is no Cost Record to show right now...");
		else{
			NodeType *p = plist; for(int s=0; s<start && p!=NULL; s++) p = p->next;
			for(int i=0; i<20 && p!=NULL; i++){
				CostRecord *costInfo = (CostRecord *)(p->info);
				char buffer[20]; Date d = costInfo->date;
				sprintf(buffer, "%d", start+i+1);				printAt(11,4+i,buffer);
				sprintf(buffer, "%s", costInfo->name);			printAt(21,4+i,buffer);
				sprintf(buffer, "%d", costInfo->qty);			printAt(48,4+i,buffer);
				sprintf(buffer, "%.2f", costInfo->unitprice);	printAt(63,4+i,buffer);
				sprintf(buffer, "%d/%d/%d", d.dd, d.mm, d.yy);	printAt(80,4+i,buffer);
				p = p->next;
			}
		}
		if(mode == 0){
			printAt(1,25, "----------------------------------------------------------------------------------------------------");
			printAt(11,26, "(B)ack     (S)earch     Sort by (D)ate     (R)emove to Cost          Your Option :");
		}
		else{
			printAt(1,28, "----------------------------------------------------------------------------------------------------");
			printAt(11,29, "Press any key to go back to Cost Record List...");
			getch(); break;
		}
		
		key = getArrowKey();
		if(key == 72 && start > 0) start--;
		else if(key == 80 && start < count - 1) start++;
		else if(key == 'S' || key == 's'){
			char search[20];
			printAt(11,28, "Enter Product Name to Search :");
			moveCursorTo(42, 28);	scanf("%s",search);
			searchCostRecord(search);
		}
		else if(key == 'D' || key == 'd'){
			while(1){
				printAt(11,28, "Enter 0 to Sort from Oldest to Newest");
				printAt(11,29, "Enter 1 to Sort from Newest to Oldest");
				int sort; moveCursorTo(68,29); scanf("%d",&sort);
				if(sort == 0)		sortCostRecord(0);
				else if(sort == 1)	sortCostRecord(1);
				break;
			}
		}
		else if(key == 'R' || key == 'r'){
			if(listCount(costlist) == 0){
				printAt(11,29, "There is nothing to Remove. Cost Record is Empty.");
				getch();	continue;
			}
			printAt(11,28, "Enter index of Cost Record to Remove :");
			int remove; moveCursorTo(52,28); scanf("%d",&remove);
			if((remove>0)&&(remove<=listCount(costlist))){
				removeCostRecord(remove);		plist = costlist;
				printAt(11,29, "Removed to Inventory Successfully! (Undo Expense)");
				getch();
			}
			else{
				printAt(11,29, "Error : Invalid Index! Try Again.");
				getch();
			}
		}
		else if(key == 'B' || key == 'b') break;
	}
}
void searchCostRecord(char name[20]){
	if(costlist == NULL) return;
	NodeType *foundlist = NULL, *foundtail = NULL, *ptr = costlist;	int found = 0;
	while(ptr != NULL){
		CostRecord *costInfo = (CostRecord *)(ptr->info);
		if(strcmp(name, costInfo->name)==0){
			NodeType *temp = GetNode();
			if(temp == NULL){
				printf("\nError : Can't get new memory space for Node."); return;
			}
			temp->info = malloc(sizeof(Purchase));
			if (temp->info == NULL) {
		    	printf("\nError : Can't get new memory space for Info.");
				free(temp);	return;
			}
			
			CostRecord *tempInfo = (CostRecord *)(temp->info);
			copyCostRecord(tempInfo, costInfo);
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
	showCostRecord(foundlist, 1);
	FreeList(foundlist);
}
void sortCostRecord(int flag){
	//flag = 0 : Oldest to Newest
	//flag = 1 : Newest to Oldest
	if(costlist == NULL)				return;		//list has no data so don't sort
	else if(costlist->next == NULL)		return;		//list only has 1 data so no need to sort
	
	NodeType *p = costlist;
	NodeType *ptr = costlist;
	NodeType *mm = ptr;	//mm for min/max
	
	while(p != NULL){
		//This inner while loop find min
		while(ptr != NULL){
			CostRecord *ptrInfo = (CostRecord*)(ptr->info);
			CostRecord *mmInfo = (CostRecord*)(mm->info);
			if((flag == 0 && dateValue(ptrInfo->date) < dateValue(mmInfo->date))
			|| (flag == 1 && dateValue(ptrInfo->date) > dateValue(mmInfo->date))){
				mm = ptr;
			}
			ptr = ptr->next;
		}
		CostRecord *pInfo = (CostRecord*)(p->info);
		CostRecord *mmInfo = (CostRecord*)(mm->info);
		CostRecord tempInfo;

		//Swap current node (p) with the min/max node found
		//Swap only info, the address and next linking still same
		copyCostRecord(&tempInfo, pInfo);
		copyCostRecord(pInfo, mmInfo);
		copyCostRecord(mmInfo, &tempInfo);

		//Reset where pointers begin
		p = p->next; mm = p; ptr = p;
	}
}
void removeCostRecord(int costNo){
	NodeType *bef, *ptr = costlist;		int i=1;
	while(i<costNo && ptr!=NULL){
		i++;	bef = ptr;	ptr = ptr->next;
	}
	
	CostRecord *costInfo = (CostRecord *)(ptr->info);
	inputInventory(costInfo->name, costInfo->qty, costInfo->unitprice);
	if(ptr == costlist){
		costlist = costlist->next;
		FreeNode(ptr);
		return;
	}
	else{
		bef->next = ptr->next;
		FreeNode(ptr);
		return;
	}
	getch();
}
