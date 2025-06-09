#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "data.h"
#include "inventoryMode.h"
#include "costrecordMode.h"
void loadInventory(){
	FILE *fp = fopen("inventoryFile.txt", "r");
	if(fp == NULL) return;
	Inventory p;	NodeType *ptr = invlist;
	if(ptr != NULL) while(ptr->next != NULL) ptr = ptr->next;
	while(fscanf(fp, "%[^,],%d,%f\n", p.name, &p.totalqty, &p.avgprice) == 3){
		NodeType *inv = GetNode();
		if(inv == NULL){
			printf("\nError: Can't get new memory space for Node."); return;
		}
		inv->info = malloc(sizeof(Inventory));
		if (inv->info == NULL) {
	    	printf("Error : Can't get new memory space for Info.");
			free(inv);	return;
		}
		*(Inventory *)(inv->info) = p;
		if(ptr == NULL){
			invlist = inv;
			ptr = inv;
		}else{
			ptr->next = inv;
			inv->next = NULL;
			ptr = ptr->next;
		}
	}
	fclose(fp);
}
void saveInventory(){
	NodeType *p = invlist;
	FILE *fp = fopen("inventoryFile.txt", "w");
	while(p != NULL){
		Inventory *invInfo = (Inventory *)(p->info);
		fprintf(fp, "%s,%d,%f\n", invInfo->name, invInfo->totalqty, invInfo->avgprice);
		p = p->next;
	}
	fclose(fp);
}
void copyInventory(Inventory *p1, Inventory *p2){
	strcpy(p1->name, p2->name);
	p1->totalqty = p2->totalqty;
	p1->avgprice = p2->avgprice;
}

void inputInventory(char n[20], int q, float p){
	int found = 0;	NodeType *temp = invlist;
	while(temp != NULL){
		Inventory *invInfo = (Inventory *)(temp->info);
		if(strcmp(invInfo->name, n)==0){
			invInfo->avgprice = ((invInfo->avgprice * invInfo->totalqty) + (p * q))/(invInfo->totalqty + q);
			invInfo->totalqty = invInfo->totalqty + q;
			found = 1;	break;
		}
		temp = temp->next;
	}
	if(found == 0){
		NodeType *newInv;	newInv = GetNode();
		if(newInv == NULL){
			printf("\nError: Can't get new memory space for Node."); return;
		}
		newInv->info = malloc(sizeof(Inventory));
		if (newInv->info == NULL) {
    		printf("\nError : Can't get new memory space for Info.");
			free(newInv);	return;
		}
		Inventory *invInfo = (Inventory *)(newInv->info);
		strcpy(invInfo->name, n);
		invInfo->totalqty = q;
		invInfo->avgprice = p;
		newInv->next = NULL;
		
		if(invlist == NULL){
			invlist = newInv;
		}
		else{
			NodeType *last = invlist;
			while(last->next != NULL){
				last = last->next;
			}
			last->next = newInv;
		}
	}
}
void showInventory(NodeType *plist, int mode){
	//mode = 0 : show full Inventory List
	//mode = 1 : show filtered Inventory List
	char key; int start = 0;
	while(1){
		int count = listCount(plist);	system("cls");
		printAt(19,1,  "No.          Product Name         Quantity          Unit Price");
		printAt(1,2,  "----------------------------------------------------------------------------------------------------");
		if(plist == NULL)	printAt(7,4, "There is no Inventory to show right now...");
		else{
			NodeType *p = plist; for(int s=0; s<start && p!=NULL; s++) p = p->next;
			for(int i=0; i<17 && p!=NULL; i++){
				Inventory *invInfo = (Inventory *)(p->info);
				char buffer[20];
				sprintf(buffer, "%d", start+i+1);				printAt(19,4+i,buffer);
				sprintf(buffer, "%s", invInfo->name);			printAt(32,4+i,buffer);
				sprintf(buffer, "%d", invInfo->totalqty);		printAt(53,4+i,buffer);
				sprintf(buffer, "%.2f", invInfo->avgprice);		printAt(71,4+i,buffer);
				p = p->next;
			}
		}
		if(mode == 0){
			printAt(1,22, "----------------------------------------------------------------------------------------------------");
			printAt(7,23, "(B)ack     (S)earch     Sort by (Q)uantity     (R)emove to Cost          Your Option :");
		}
		else{
			printAt(1,27, "----------------------------------------------------------------------------------------------------");
			printAt(7,28, "Press any key to go back to Inventory List...");
			getch(); break;
		}
		
		key = getArrowKey();
		if(key == 72 && start > 0) start--;
		else if(key == 80 && start < count - 1) start++;
		else if(key == 'S' || key == 's'){
			char search[20];
			printAt(7,25, "Enter Product Name to Search :");
			moveCursorTo(38, 25);	scanf("%s",search);
			searchInventory(search);
		}
		else if(key == 'Q' || key == 'q'){
			while(1){
				printAt(7,25, "Enter 0 to Sort from Lowest to Highest");
				printAt(7,26, "Enter 1 to Sort from Highest to Lowest");
				int sort; moveCursorTo(46,26); scanf("%d",&sort);
				if(sort == 0)		sortInventory(0);
				else if(sort == 1)	sortInventory(1);
				break;
			}
		}
		else if(key == 'R' || key == 'r'){
			if(count == 0){
				printAt(7,25, "There is nothing to Remove. Inventory is Empty.");
				getch();	continue;
			}
			printAt(7,25, "Enter Inventory Record to Remove...");
			int i,q;		int d,m,y;
			printAt(7,26, "Product Index No. :");	moveCursorTo(27,26);	scanf("%d",&i);
			if(i<1 || i>count){
				printAt(7,27, "Error : Invalid Index! Try Again.");
				getch();	continue;
			}
			printAt(7,27, "Product Quantity :");	moveCursorTo(27,27);	scanf("%d",&q);
			printAt(7,28, "Date of Removal :");		moveCursorTo(27,28);	scanf("%d %d %d",&d,&m,&y);
			
			NodeType *ptr = invlist;
			for(int j=1; j<i; j++){
				ptr = ptr->next;
			}
			Inventory *ptrInfo = (Inventory *)(ptr->info);
			//copy ptrInfo to temp before it successfully delete and might freed memory
			char tempName[20];	float tempAvgprice;
			strcpy(tempName, ptrInfo->name);
			tempAvgprice = ptrInfo->avgprice;
			if(!removeInventory(ptrInfo->name, q, ptrInfo->avgprice)){
				printAt(7,29, "Error : Not Enough Inventory to Remove!");
				getch();	continue;
			}
			
			//when q<totalqty = successfully removed = add to cost
			Date removeDate;	removeDate.dd = d; removeDate.mm = m; removeDate.yy = y;
			inputCostRecord(tempName, q, tempAvgprice, removeDate);
			printAt(7,29, "Removed to Cost Record Successfully! (Used Ingredients)");
			getch();
		}
		else if(key == 'B' || key == 'b') break;
	}
}
void searchInventory(char n[20]){
	if(invlist == NULL) return;
	NodeType *foundlist = NULL, *foundtail = NULL, *ptr = invlist;	int found = 0;
	while(ptr != NULL){
		Inventory *invInfo = (Inventory *)(ptr->info);
		if(strcmp(n, invInfo->name)==0){
			NodeType *temp = GetNode();
			if(temp == NULL){
				printf("\nError : Can't get new memory space for Node."); return;
			}
			temp->info = malloc(sizeof(Inventory));
			if (temp->info == NULL) {
		    	printf("\nError : Can't get new memory space for Info.");
				free(temp);	return;
			}
			
			Inventory *tempInfo = (Inventory *)(temp->info);
			copyInventory(tempInfo, invInfo);
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
	showInventory(foundlist, 1);
	FreeList(foundlist);
}
void sortInventory(int flag){
	//flag = 0 : Lowest to Highest
	//flag = 1 : Highest to Lowest
	if(invlist == NULL)				return;		//list has no data so don't sort
	else if(invlist->next == NULL)	return;		//list only has 1 data so no need to sort
	
	NodeType *p = invlist;
	NodeType *ptr = invlist;
	NodeType *mm = ptr;	//mm for min/max
	
	while(p != NULL){
		//This inner while loop find min
		while(ptr != NULL){
			Inventory *ptrInfo = (Inventory*)(ptr->info);
			Inventory *mmInfo = (Inventory*)(mm->info);
			if((flag == 0 && ptrInfo->totalqty < mmInfo->totalqty)
			|| (flag == 1 && ptrInfo->totalqty > mmInfo->totalqty)){
				mm = ptr;
			}
			ptr = ptr->next;
		}
		Inventory *pInfo = (Inventory*)(p->info);
		Inventory *mmInfo = (Inventory*)(mm->info);
		Inventory tempInfo;

		//Swap current node (p) with the min/max node found
		//Swap only info, the address and next linking still same
		copyInventory(&tempInfo, pInfo);
		copyInventory(pInfo, mmInfo);
		copyInventory(mmInfo, &tempInfo);

		//Reset where pointers begin
		p = p->next; mm = p; ptr = p;
	}
}
bool removeInventory(char n[20], int q, float p){
	NodeType *ptr = invlist;	int found = 0;
	while(ptr != NULL){
		Inventory *invInfo = (Inventory *)(ptr->info);
		if(strcmp(n, invInfo->name)==0 && q<= invInfo->totalqty){
			found = 1;	break;
		}
		ptr = ptr->next;
	}
	if(found == 0) return false;
	
	Inventory *invInfo = (Inventory *)(ptr->info);
	if(q == invInfo->totalqty){
		if(ptr == invlist)	invlist = invlist->next;
		else{
			NodeType *prev = invlist;
			while(prev->next != ptr) prev = prev->next;
			prev->next = ptr->next;
		}
		FreeNode(ptr);
	}
	else{
		invInfo->avgprice = ((invInfo->avgprice * invInfo->totalqty) - p*q)/(invInfo->totalqty - q);
		invInfo->totalqty = invInfo->totalqty - q;
	}
	return true;
}
