#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<assert.h>

#define BYTE unsigned char
#define MAXPRICE 0
#define MAXROOM 1
#define MINROOM 2
#define DATE 3
#define ENTER 4
#define SORT 5
#define N 7
typedef struct date
{
	short int day;
	short int month;
	short int year;
}Date;
typedef struct apartment
{
	int code;
	char *adress;
	int price;
	short int numRooms;
	Date entrenceDate;
}Apartment;
typedef struct apartmentNode
{
	Apartment Ap;
	Date eTime;
	struct apartmentNode *next;
}APnode;
typedef struct apartmentList
{
	APnode *head;
	APnode *tail;
}APlist;
typedef struct commandlistnode
{
	int number;
	char* command;
	struct commandlistnode *next;
}CLNode;
typedef struct commandlist
{
	CLNode *head;
	CLNode *tail;
}CList;
typedef struct bits
{
	BYTE byte1;
	BYTE byte2;
	BYTE byte3;
	BYTE byte4;
	BYTE byte5;
}bits;

char *getcommand();
void get_an_apt(char *token, APlist lst);
APnode* createNewAPNode(Apartment AP, Date time, APnode * next);
void freeAPList(APlist *lst);
APnode ** sort_s(APlist lst, APnode* *arr, int *size);
APnode ** sort_sr(APlist lst, APnode* *arr, int *size);
void printApt(Apartment ap);
Date numToDate(int num);
void searchTheApartments(APlist lst, Apartment arr[]);
void insertDataToEndList(APlist *lst, Apartment ap, Date time);
void swap(APnode **xp, APnode **yp);
bool isEmptyList(APlist lst);
int countItemsInList(APlist lst);
void add_an_apt(APlist *lst, char *string, int *serialNum);
APnode* createNewListNode(int code, char *adress, int price, short int numRooms, Date entrenceDate, APnode * next);
void insertData1ToEndList(APlist* lst, int code, char *adress, int price, short int numRooms, Date entrenceDate);
void makeEmptyList(APlist *lst);
bool evacuateuntil(Date current, Date destanation);
bool enterdinlastdays(Date date, int past);
void freearr(APnode* *arr, int size);
void printDataBaseEntryDate(Date etime);
void buy_an_apt(APlist *lst, char *code, int *serialNum);
Date getDataBaseEntryDate(char *etime);
void delete_an_apt(APlist *lst, char *num, int *serialNum);
void putinmemory(char* command, char* short_term_history[N], CList *commandList, int *size, int *numcommand);
CLNode* createNewCharNode(char* command, int numcommand, CLNode *next);
bool isEmptyCList(CList lst);
void insertCharToEndList(CList *lst, CLNode *newTail);
void insertCharDataToEndList(CList *lst, int numcommand, char *command);
void printShortHistory(char *arr[N], int shorthistory, int oldhistory);
void printHistory(char *arr[N], CList commandList, int shorthistory, int oldhistory);
void docommand(char *command, APlist *list, int *serialNum);
char* getcommandbynum(char* command, char *arr[N], CList commandList, int shortermsize, int longtermsize);
void savecommands(char *arr[N], int shorthistory, CList commandList, int oldhistory);
void savelistrec(CLNode *root, FILE *f);
void loadcommands(char *arr[N], int *shorthistory, CList *commandList, int *oldhistory);
void putinmemorybackward(char* command, char* short_term_history[N], CList *commandList, int *size, int *numcommand);
void insertCharToHeadList(CList *lst, CLNode *newHead);
void insertCharDataToHeadList(CList *lst, int numcommand, char *command);
bits createbitsfromap(APnode ap);
void loadapartments(APlist *lst, int *serialNum);
void saveapartments(APlist *lst);
void createapfrombits(bits bit, APnode**res);
void NullTheArray(char* short_term_history[N]);
void makeEmptyCList(CList *lst);
void mainCommand(APlist *list, CList *oldCommandList, char  *short_term_history[N], int *serialNum, int * shortTermSize, int* longtermsize);
void freeCMList(CList *lst);
void freeSCArr(char  *short_term_history[N], int size);
void insertNodeToEndList(APlist* lst, APnode * newTail);