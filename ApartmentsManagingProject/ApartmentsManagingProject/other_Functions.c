#include "MainHeader.h"

void swap(APnode **xp, APnode **yp)//basic swaping function.
{
	APnode *temp;
	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

int countItemsInList(APlist lst)//counts the number of items in the apartment list.
{
	APnode *curr = lst.head;
	int i = 0;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return i;
}

Date getDataBaseEntryDate(char *etime)/*get string give date struct*/
{
	int day, month, year;
	char *ttime = strdup(etime);
	Date TIME;
	char *token;
	char *seps = " ";
	token = strtok(ttime, seps);
	token = strtok(NULL, seps);
	if (strcmp(token, "Jan") == 0)
		month = 1;
	if (strcmp(token, "Feb") == 0)
		month = 2;
	if (strcmp(token, "Mar") == 0)
		month = 3;
	if (strcmp(token, "Apr") == 0)
		month = 4;
	if (strcmp(token, "May") == 0)
		month = 5;
	if (strcmp(token, "Jun") == 0)
		month = 6;
	if (strcmp(token, "Jul") == 0)
		month = 7;
	if (strcmp(token, "Aug") == 0)
		month = 8;
	if (strcmp(token, "Sep") == 0)
		month = 9;
	if (strcmp(token, "Oct") == 0)
		month = 10;
	if (strcmp(token, "Nov") == 0)
		month = 11;
	if (strcmp(token, "Dec") == 0)
		month = 12;
	token = strtok(NULL, seps);
	sscanf(token, "%d", &day);
	token = strtok(NULL, seps);
	token = strtok(NULL, seps);
	sscanf(token, "%d", &year);
	free(ttime);
	TIME.day = day;
	TIME.month = month;
	TIME.year = year - 2000;
	return TIME;
}

Date numToDate(int num)/*get many numbers and extract date struct*/
{
	Date res;
	int dig;
	int power = 1;
	int num2 = 0;
	int i = 0;
	while (i<4)
	{
		dig = num % 10;
		num2 = num2 + dig*power;
		power *= 10;
		num /= 10;
		i++;
	}
	res.year = num2 - 2000;
	num2 = 0;
	power = 1;
	while (i < 6)
	{
		dig = num % 10;
		num2 = num2 + dig*power;
		power *= 10;
		num /= 10;
		i++;
	}
	res.month = num2;
	num2 = 0;
	power = 1;
	while (i < 8)
	{
		dig = num % 10;
		num2 = num2 + dig*power;
		power *= 10;
		num /= 10;
		i++;
	}
	res.day = num2;
	return res;
}

void NullTheArray(char *short_term_history[N])/*put null in fields*/
{
	for (int i = 0; i < N; i++)
		short_term_history[i] = NULL;
}