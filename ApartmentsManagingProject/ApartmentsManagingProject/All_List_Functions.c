#include "MainHeader.h"

APnode* createNewAPNode(Apartment AP, Date time, APnode * next)//Creates the node for the Apartment List.
{
	APnode* res;

	res = (APnode*)malloc(sizeof(APnode));
	res->Ap.code = AP.code;
	res->Ap.adress = strdup(AP.adress);
	res->Ap.entrenceDate = AP.entrenceDate;
	res->Ap.numRooms = AP.numRooms;
	res->Ap.price = AP.price;

	res->eTime = time;
	res->next = next;

	return res;
}

void insertNodeToEndList(APlist* lst, APnode * newTail)//Inserts the node to the end of the list
{
	if (isEmptyList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

bool isEmptyList(APlist lst)//checks if the apartment list is empty or not
{
	return (lst.head == NULL);
}

bool isEmptyCList(CList lst)//checks if the command list is empty or not
{
	return (lst.head == NULL);
}

void insertDataToEndList(APlist *lst, Apartment ap, Date time)//inserts the data to the apartment list.
{
	APnode* newTail;

	newTail = createNewAPNode(ap, time, NULL);
	insertNodeToEndList(lst, newTail);
}

APnode* createNewListNode(int code, char *adress, int price, short int numRooms, Date entrenceDate, APnode * next)//creates new apartment list node with all the data in the apartment.
{
	APnode* res;
	time_t currentTime;
	char *ntime;
	res = (APnode*)malloc(sizeof(APnode));
	res->Ap.code = code;
	res->Ap.adress = (char*)malloc(strlen(adress) * sizeof(char) + 1);
	strcpy(res->Ap.adress, adress);
	res->Ap.price = price;
	res->Ap.numRooms = numRooms;
	res->Ap.entrenceDate.day = entrenceDate.day;
	res->Ap.entrenceDate.month = entrenceDate.month;
	res->Ap.entrenceDate.year = entrenceDate.year;
	time(&currentTime);
	ntime = ctime(&currentTime);

	res->eTime = getDataBaseEntryDate(ntime);

	res->next = next;

	return res;
}

void insertData1ToEndList(APlist* lst, int code, char *adress, int price, short int numRooms, Date entrenceDate)//inserts the data to the apartment list with all argument.
{
	APnode* newTail;

	newTail = createNewListNode(code, adress, price, numRooms, entrenceDate, NULL);
	insertNodeToEndList(lst, newTail);
}

void makeEmptyList(APlist *lst)//makes empty list
{
	lst->head = NULL;
	lst->tail = NULL;
}

void makeEmptyCList(CList *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

CLNode* createNewCharNode(char* command, int numcommand, CLNode *next)//creates new node for command list
{
	CLNode *res;
	res = (CLNode*)malloc(sizeof(CLNode));
	res->command = strdup(command);
	res->number = numcommand;
	res->next = next;
	return res;
}

void insertCharToEndList(CList *lst, CLNode *newTail)//inserts node command to end of list
{

	if (isEmptyCList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void insertCharDataToEndList(CList *lst, int numcommand, char *command)//inserts command node data to end list.
{
	CLNode* newTail;

	newTail = createNewCharNode(command, numcommand, NULL);
	insertCharToEndList(lst, newTail);
}

void insertCharToHeadList(CList *lst, CLNode *newHead)//inserts node command to end of list
{
	newHead->next = lst->head;
	if (lst->tail == NULL)
		lst->tail = newHead;
	lst->head = newHead;
}

void insertCharDataToHeadList(CList *lst, int numcommand, char *command)//inserts command node data to end list.
{
	CLNode* newHead;

	newHead = createNewCharNode(command, numcommand, NULL);
	insertCharToHeadList(lst, newHead);
}