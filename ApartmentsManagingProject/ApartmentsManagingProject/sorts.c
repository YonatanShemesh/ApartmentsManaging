#include "MainHeader.h"

APnode ** sort_s(APlist lst, APnode **arr, int *size)//sorts the apartments from the lowest price to the highest
{
	APnode *curr = lst.head;
	*size = countItemsInList(lst);//gets the number of items in the list
	arr = (APnode**)malloc(*size * sizeof(APnode*));
	int i, j;
	for (i = 0; (i < *size) && (curr != NULL); i++)
	{
		arr[i] = curr;
		curr = curr->next;
	}
	for (i = 0; i < *size - 1; i++)//bubble sort 
	{
		for (j = *size - 1; j >i; j--)
		{
			if (arr[j]->Ap.price <arr[j - 1]->Ap.price)
				swap(&arr[j], &arr[j - 1]);
		}
	}
	return arr;
}

APnode ** sort_sr(APlist lst, APnode **arr, int *size)//sorts the apartments from the highest price to the lowest.
{
	APnode *curr = lst.head;
	*size = countItemsInList(lst);
	arr = (APnode**)malloc(*size * sizeof(APnode*));
	int i, j;
	for (i = 0; (i < *size) && (curr != NULL); i++)
	{
		arr[i] = curr;
		curr = curr->next;
	}
	for (i = 0; i < *size - 1; i++)//bubble sort
	{
		for (j = *size - 1; j >i; j--)
		{
			if (arr[j]->Ap.price >arr[j - 1]->Ap.price)
				swap(&arr[j], &arr[j - 1]);
		}
	}
	return arr;
}