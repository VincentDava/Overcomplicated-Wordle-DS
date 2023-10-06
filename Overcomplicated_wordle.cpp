#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
const int max_elemen=10;
struct node{
	char huruf;
	int index;
	node *next;
}*head[max_elemen+4],*tail[max_elemen+4];
unsigned long hash(char huruf) {
        unsigned long hash = 5381;
        int c;
        while ((c = huruf++))
            hash = ((hash << 5) + hash) + c; 
        return hash % max_elemen;
}
node *createnode(char huruf,int index){
	node *newnode = (node *)malloc(sizeof(node));
	newnode->huruf=huruf;
	newnode->index=index;
	newnode->next = NULL;
	return newnode;
}
void insert(char huruf,int index){
	int idx = hash(huruf);
	node *newnode = createnode(huruf,index);
	if(head[idx] == NULL || tail[idx] == NULL){

		head[idx]= tail[idx] = newnode;
	}else{
		tail[idx]->next = newnode;
		tail[idx]=newnode;

	}
}
int searching(char huruf,int index){	
	int idx = hash(huruf);
	if(head[idx]==NULL){
		return -1;
	}else{
		if(head[idx]->huruf==huruf&&head[idx]->index==index){
			return 10;
		}else if(head[idx]->huruf==huruf){
			return 5;
		}else{
			node *curr = head[idx]->next;
			while(curr){
				if(curr->huruf==huruf&&curr->index==index){
					return 10;
				}else if(curr->huruf==huruf){
					return 5;
				}
				curr=curr->next;
			}
		}
	}
	return -1;
}
void pop(char huruf){
		int idx = hash(huruf);
	if(head[idx]==NULL){
	}else{
	
		if(head[idx]->huruf==huruf){
		
			node *temp = head[idx];
			head[idx] = head[idx]->next;
			temp->next=NULL;
			free(temp);
		}else{

			node *curr = head[idx];

			while(curr->next){
				if(curr->next->huruf==huruf){
		
					node *temp =curr->next;
		
					curr->next=curr->next->next;
					
					temp->next=NULL;
					free(temp);
					temp=NULL;
				}
				curr=curr->next;
			}
		}
	}
}
void home(){
	printf("OVERCOMPLICATED WORDLE\n");
	printf("======================\n");
	printf("1. Play\n");
	printf("2. Exit\n");
	printf("Choose : ");
}
int main(){
	char wordlist[300][100];
	int p=0;
	int a=0;
		int j=0;
	char inserted[100];
	FILE *fp=fopen("word.list","r+");
	while(!feof(fp)){
		fscanf(fp,"%s\n",wordlist[p]);
		p++;
	}
	do{
	home();
	scanf("%d",&a);
	getchar();
	int num=0;
	if(a==1){
		srand(time(NULL)); 
		num=(rand()%(p-1-0+1))+0;
		for(int i=0;i<strlen(wordlist[num]);i++){
			insert(wordlist[num][i],i);
		}
	int checking[20];
	int win=0;
	int totw=0;
	int ty=0;
	do{
	printf("\nHow to play: write 6 alphabet character and guess the word using the hint!\n\n");
	printf("\nG -> The word exist and is in the right position \n");
	printf("Y -> The word is correct but is not in the right position\n");
	do{
	win=0;
	printf("    Attempt %d/6 \n",ty);
	scanf("%s",inserted);
	getchar();
	if(strlen(inserted)!=6){
		printf("Do not type more/less than 6 characters !\n");
	}
	}while(strlen(inserted)!=6);
	ty=ty+1;
	char checksame[20];
	int doublez=0;
	int i=0;
	for(i=0;i<strlen(inserted);i++){
		checking[i]=searching(inserted[i],i);
		for(int q=0;q<i;q++){
			if(checksame[q]==inserted[i] && checking[i]==10){
				doublez=0;
				checking[q]=-1;
			}
			else if(checksame[q]==inserted[i]){
				checking[i]=-1;
			}
		}
		
		checksame[i]=inserted[i];
		}
		
		for(int w=0;w<=i;w++)
		if(checking[w]==10){//green
		printf("G");
			win+=1;
		}else if(checking[w]==5){//yellow
			printf("Y");
		}else if(checking[w]==-1){
			printf(" ");
		}
		if(win==6){
			break;
		}
		totw+=win;
	}while(ty<7&&win<6);
	if(win==6){
		printf("\nYou got the word!\n");
	}else if(totw>0){
		printf("\nYou didn't find the word! It was...\n%s",wordlist[num-1]);
	}else{
		printf("\nYou didn't get the word!\nNext Attempt!\nPress enter to continue..\n");
		getchar();
	}
	}else if(a==2){
		return 0;
	}
		for(int k=0;k<strlen(wordlist[num]);k++){
			pop(wordlist[num][k]);
		}
}while(true);
return 0;
}
