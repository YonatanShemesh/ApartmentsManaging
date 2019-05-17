#include "MainHeader.h"


void savecommands(char *arr[N], int shorthistory, CList commandList, int oldhistory)/*save command to file*/
{
	int i;
	FILE* ftext;
	ftext = fopen("command.txt", "wt");
	assert(ftext != NULL);
	if (oldhistory == 0)
	{
		for (i = shorthistory - 1; i >= 0; i--)
		{
			fputs(arr[i], ftext);
			fputc('\n', ftext);
		}
	}
	else
	{
		for (i = N - 1; i >= 0; i--)
		{

			fputs(arr[i], ftext);
			fputc('\n', ftext);
		}
		savelistrec(commandList.head, ftext);
	}
	fclose(ftext);
}

void savelistrec(CLNode *root, FILE *f)/*save to fil in rec*/
{
	if (root == NULL)
		return;
	savelistrec(root->next, f);

	fputs(root->command, f);
	fputc('\n', f);
}

void loadcommands(char *arr[N], int *shorthistory, CList *commandList, int *oldhistory)/*loads command from file*/
{
	*shorthistory = 0;
	*oldhistory = 0;
	char* temp[N];
	int len, char1;
	int Lsize = 0, Psize = 2;
	CLNode *curr;
	char *command;
	FILE *f = fopen("command.txt", "r+t");
	if (f == NULL)
	{
		f = fopen("command.txt", "w+t");
	}
	else
	{

		fseek(f, 0, SEEK_END);
		len = (int)ftell(f);
		fseek(f, 0, SEEK_SET);
		while (((int)ftell(f)) < len)
		{
			command = (char*)malloc(2 * sizeof(char));
			char1 = fgetc(f);
			if (char1 != EOF)
			{
				while (char1 != '\n')
				{
					if (Lsize < Psize)
					{
						*(command + Lsize) = char1;
						Lsize++;
					}
					else
					{
						Psize *= 2;
						command = (char*)realloc(command, Psize * sizeof(char));
						*(command + Lsize) = char1;
						Lsize++;
					}
					char1 = fgetc(f);
				}
				char1 = '\0';
				if (Lsize < Psize)
				{
					*(command + Lsize) = char1;
					Lsize++;
				}
				else
				{
					Psize *= 2;
					command = (char*)realloc(command, Psize * sizeof(char));
					*(command + Lsize) = char1;
					Lsize++;
				}
				command = (char*)realloc(command, Lsize * sizeof(char));
				putinmemorybackward(command, arr, commandList, shorthistory, oldhistory);
				free(command);
				Lsize = 0;
				Psize = 2;
			}
		}
		int j, i = 0;
		if (*shorthistory < N)
		{
			for (j = N - 1 - (*shorthistory - 1); j < N; j++, i++)
			{
				temp[i] = arr[j];
			}
			for (i = 0; i < N; i++)
			{
				if (i < *shorthistory)
					arr[i] = temp[i];
				else
					arr[i] = NULL;
			}
		}
		else
		{
			curr = commandList->head;
			i = 1;
			while (curr != NULL)
			{
				curr->number = i;
				curr = curr->next;
				i++;
			}
		}
	}
	fclose(f);
}