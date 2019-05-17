#include "MainHeader.h"

void freeAPList(APlist *lst)//free the apartment list.
{
	APnode *curr = (*lst).head, *saver;

	while (curr != NULL)
	{
		saver = curr->next;
		free(curr->Ap.adress);
		free(curr);
		curr = saver;
	}
}

void freeCMList(CList *lst)//free the command list.
{
	CLNode *curr = (*lst).head, *saver;

	while (curr != NULL)
	{
		saver = curr->next;
		free(curr->command);
		free(curr);
		curr = saver;
	}
}

void freeSCArr(char  *short_term_history[N],int size)//free the command list.
{
	for (int i = 0; i < size; i++)
	{
		free(short_term_history[i]);
	}
}

void freearr(APnode* *arr, int size)//free the apartment node
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(arr[i]->Ap.adress);
		free(arr[i]);
	}
}