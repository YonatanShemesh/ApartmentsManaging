#include "MainHeader.h"

void printApt(Apartment ap)
{
	printf("Apt details:\n");
	printf("Code: %d \n", ap.code);
	printf("Adress: %s \n", ap.adress);
	printf("Number of rooms: %d \n", ap.numRooms);
	printf("Price: %d \n", ap.price);
	printf("Entry date: %d.%d.%d\n", ap.entrenceDate.day, ap.entrenceDate.month, ap.entrenceDate.year + 2000);
}

void printDataBaseEntryDate(Date etime)
{
	printf("Database entry date: %d.%d.%d\n", etime.day, etime.month, etime.year + 2000);
}

void printShortHistory(char *arr[N], int shorthistory, int oldhistory)
{
	int i;
	if (shorthistory == N)
	{
		for (i = 0; i < N; i++)
		{
			printf("%d: %s \n", i + (oldhistory)+1, arr[i]);
		}
	}
	else
	{
		for (i = 0; i < (shorthistory); i++)
		{
			printf("%d: %s \n", i + 1, arr[i]);
		}
	}
}

void printHistory(char *arr[N], CList commandList, int shorthistory, int oldhistory)
{
	CLNode *curr = commandList.head;
	int i;
	if (oldhistory == 0)
	{
		for (i = 0; i < (shorthistory); i++)
		{
			printf("%d: %s \n", i + 1, arr[i]);
		}
	}
	else
	{
		while (curr != NULL)
		{
			printf("%d: %s \n", curr->number, curr->command);
			curr = curr->next;
		}
		for (i = 0; i < N; i++)
		{
			printf("%d: %s \n", i + (oldhistory)+1, arr[i]);
		}
	}
}