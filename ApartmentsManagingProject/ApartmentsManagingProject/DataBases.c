#include "MainHeader.h"

void putinmemory(char* command, char* short_term_history[N], CList *commandList, int *size, int *numcommand)
{
	char* temp[N];
	int j = 0;
	if (*size<N)//checks if the array of commands is full or not.
	{
		short_term_history[*size] = strdup(command);//inserts the command to the array
		(*size)++;
	}
	else//array is full.
	{
		(*numcommand)++;
		insertCharDataToEndList(commandList, *numcommand, short_term_history[0]);//inserts the oldest command to the list.
		for (int i = 1; i < N; i++)//saves all the commands in temp array.
		{
			temp[j] = short_term_history[i];
			j++;
		}
		free(short_term_history[0]);//free the array.
		for (int i = 0; i < N - 1; i++)//brings back the commands to the array.
		{
			short_term_history[i] = temp[i];
		}
		short_term_history[N - 1] = strdup(command);
	}
}

void putinmemorybackward(char* command, char* short_term_history[N], CList *commandList, int *size, int *numcommand)
{
	int j = 0, i = 0;
	if (*size<N)//checks if the array of commands is full or not.
	{
		short_term_history[N - 1 - (*size)] = strdup(command);//inserts the command to the array
		(*size)++;
	}
	else
	{
		(*numcommand)++;
		insertCharDataToHeadList(commandList, *numcommand, command);//inserts the oldest command to the list.
	}
}