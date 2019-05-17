#include "MainHeader.h"

void searchTheApartments(APlist lst, Apartment arr[])/*search specific apartment and print*/
{
	APlist newlist;
	int size, i;
	APnode* *sarr = NULL;
	newlist.head = newlist.tail = NULL;
	APnode *curr = lst.head;
	while (curr != NULL)
	{
		if ((curr->Ap.price <= arr[MAXPRICE].price || arr[MAXPRICE].price == -1) && (curr->Ap.numRooms >= arr[MINROOM].numRooms || arr[MINROOM].numRooms == -1) && (curr->Ap.numRooms <= arr[MAXROOM].numRooms || arr[MAXROOM].numRooms == -1) && (evacuateuntil(curr->Ap.entrenceDate, arr[DATE].entrenceDate) || arr[DATE].entrenceDate.year == -1) && (enterdinlastdays(curr->eTime, arr[ENTER].code) || arr[ENTER].code == -1))
		{
			insertDataToEndList(&newlist, curr->Ap, curr->eTime);
		}
		curr = curr->next;
	}
	curr = newlist.head;
	if (arr[SORT].code == 0)
	{
		while (curr != NULL)
		{
			printApt(curr->Ap);
			printDataBaseEntryDate(curr->eTime);
			curr = curr->next;
		}
		freeAPList(&newlist);
	}
	else if (arr[SORT].code == 1)
	{
		sarr = sort_sr(newlist, sarr, &size);
		for (i = 0; i < size; i++)
		{
			printApt(sarr[i]->Ap);
			printDataBaseEntryDate(sarr[i]->eTime);
		}
		freeAPList(&newlist);
		free(sarr);
	}
	else if (arr[SORT].code == -1)
	{
		sarr = sort_s(newlist, sarr, &size);
		for (i = 0; i < size; i++)
		{
			printApt(sarr[i]->Ap);
			printDataBaseEntryDate(sarr[i]->eTime);
		}
		freeAPList(&newlist);
		free(sarr);
	}
}

bool enterdinlastdays(Date date, int past)/*function that serce what apartment enterd in last x days*/
{
	char *currentdate;
	Date currentdate1;
	time_t currentTime;
	time(&currentTime);
	currentdate = ctime(&currentTime);
	currentdate1 = getDataBaseEntryDate(currentdate);

	while (past> 0)
	{
		if (currentdate1.day == date.day&&currentdate1.month == date.month&&currentdate1.year == date.year)
			return true;
		else
		{
			past = past - 1;
			currentdate1.day = currentdate1.day - 1;
			if (currentdate1.day == 0)
			{
				if (currentdate1.month == 2 || currentdate1.month == 4 || currentdate1.month == 6 || currentdate1.month == 8 || currentdate1.month == 9 || currentdate1.month == 11 || currentdate1.month == 1)
				{
					currentdate1.day = 31;
					currentdate1.month = currentdate1.month - 1;
					if (currentdate1.month == 0)
					{
						currentdate1.month = 12;
						currentdate1.year = currentdate1.year - 1;
					}
				}
				else if (currentdate1.month == 5 || currentdate1.month == 7 || currentdate1.month == 10 || currentdate1.month == 12)
				{
					currentdate1.day = 30;
					currentdate1.month = currentdate1.month - 1;
				}
				else if (currentdate1.month == 3)
				{
					currentdate1.day = 28;
					currentdate1.month = currentdate1.month - 1;
				}
			}
		}
	}
	return false;
}

bool evacuateuntil(Date current, Date destanation)/*function that serce what apartment evacuate in the next x days*/
{
	if (current.year < destanation.year)
	{
		return true;
	}
	else if (current.year > destanation.year)
	{
		return false;
	}
	else if (current.year == destanation.year)
	{
		if (current.month < destanation.month)
		{
			return true;
		}
		else if (current.month > destanation.month)
		{
			return false;
		}
		else if (current.month == destanation.month)
		{
			if (current.day <= destanation.day)
			{
				return true;
			}
			else
				return false;
		}
	}
}
