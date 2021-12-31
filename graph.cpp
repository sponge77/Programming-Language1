#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
using namespace std;
//dlinkedlist.h
typedef int LData;
typedef struct _node{
	LData data;
	struct _node * next;
}Node;

typedef struct _linkedList{
	Node *head;
	Node *cur;
	Node *before;
	int numOfData;
	int(*comp)(LData d1, LData d2);
}LinkedList;

typedef LinkedList List;
void ListInit(List *plist);
void LInsert(List *plist, LData data);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List *plist);
int LCount(List *plist);

void SetSortRule(List *plist,int(*comp)(LData d1, LData d2));
//dlinkedlist.c
void ListInit(List *plist){
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
} 
void FInsert(List *plist, LData data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	
	(plist->numOfData)++;
}
void SInsert(List *plist, LData data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	Node *pred = plist->head;
	newNode -> data = data;
	
	while(pred->next!=NULL && plist->comp(data,pred->next->data)!=0){
		pred = pred->next;	
	}
	newNode->next = pred->next;
	pred->next = newNode;
	(plist->numOfData)++;
	
}
void LInsert(List *plist, LData data){
	if(plist->comp == NULL)
		FInsert(plist,data);
	else	
		SInsert(plist,data);
}
int LFirst(List *plist, LData *pdata){
	if(plist->head->next == NULL)
		return FALSE;
	plist -> before = plist->head;
	plist->cur = plist->head->next;
	
	*pdata = plist->cur->data;
	return TRUE;
}
int LNext(List *plist, LData *pdata){
	if(plist->cur->next==NULL)
		return FALSE;
	plist->before = plist->cur;
	plist ->cur = plist->cur->next;
	
	*pdata = plist->cur->data;
	return TRUE;
}
void SetSortRule(List *plist, int(*comp)(LData d1, LData d2)){
	plist->comp = comp;
}
//algraph.c
enum {A,B,C,D,E,F,G,H,I};


typedef struct _ual{
	int numV;
	int numE;
	List *adjList;
}ALGraph;

void GraphInit(ALGraph *pg, int nv);
void GraphDestroy(ALGraph *pg);
void AddEdge(ALGraph *pg, int fromV, int toV);
void ShowGraphEdgeInfo(ALGraph *pg);



int WhoIsPrecede(int data1,int data2);


void GraphInit(ALGraph *pg, int nv){
	int i;
	
	pg->adjList = (List*)malloc(sizeof(List)*nv);
	pg->numV = nv;
	pg->numE=0;
	
	for(i=0;i<nv;i++){
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]),WhoIsPrecede);
	}
}
void GraphDestroy(ALGraph * pg){
	if(pg->adjList != NULL)
		free(pg->adjList);
}
void AddEdge(ALGraph *pg, int fromV, int toV){
	LInsert(&(pg->adjList[fromV]),toV);
	LInsert(&(pg->adjList[toV]),fromV);
	pg->numE +=1;
}
void ShowGraphEdgeInfo(ALGraph *pg){
	int i;
	int vx;
	
	for(i=0;i<pg->numV;i++){
		printf("%c와 연결된 정점: ",i+65);
		
		if(LFirst(&(pg->adjList[i]),&vx)){
			printf("%c ",vx+65);
			
			while(LNext(&(pg->adjList[i]),&vx));
				printf("%c ",vx+65);
		}
		printf("\n");
	}
}
int WhoIsPrecede(int data1,int data2){
	if(data1<data2) return 0;
	else return 1;
}
//algraph.h


//typedef int BOOL;
//algraphmiaain.c
int main(void){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ALGraph graph;
	GraphInit(&graph,5);
	
	AddEdge(&graph,A,B);
	AddEdge(&graph,A,D);
	AddEdge(&graph,B,C);
	AddEdge(&graph,C,D);
	AddEdge(&graph,D,E);
	AddEdge(&graph,E,A);
	
	ShowGraphEdgeInfo(&graph);
	GraphDestroy(&graph);
	return 0;
}
