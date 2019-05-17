#include "MainHeader.h"

char *getcommand()/*get command with spaces*/
{
	char ch;
	char *str;
	int Lsize = 0, Psize = 2;
	str = (char*)malloc(2 * sizeof(char));
	scanf("%c", &ch);
	while (ch == '\n' || ch == ' ')
		scanf("%c", &ch);
	while (ch != '\n')
	{
		if (Lsize < Psize)
		{
			*(str + Lsize) = ch;
			Lsize++;
		}
		else
		{
			Psize *= 2;
			str = (char*)realloc(str, Psize * sizeof(char));
			*(str + Lsize) = ch;
			Lsize++;
		}
		scanf("%c", &ch);
	}
	ch = '\0';
	if (Lsize < Psize)
	{
		*(str + Lsize) = ch;
		Lsize++;
	}
	else
	{
		Psize *= 2;
		str = (char*)realloc(str, Psize * sizeof(char));
		*(str + Lsize) = ch;
		Lsize++;
	}
	str = (char*)realloc(str, Lsize * sizeof(char));

	return str;
}

void get_an_apt(char *str, APlist lst)/*serch and give to user apartmen by any order he need*/
{
	char *token;
	Apartment arr[6];
	char *seps = " ";
	token = strtok(str, seps);
	int numDate;
	arr[SORT].code = 0;
	arr[MAXPRICE].price = -1;
	arr[MINROOM].numRooms = -1;
	arr[MAXROOM].numRooms = -1;
	arr[DATE].entrenceDate.year = -1;
	arr[ENTER].code = -1;

	while (token != NULL)
	{
		if (strcmp(token, "-MaximumPrice") == 0)
		{
			sscanf(strtok(NULL, seps), "%d", &((arr[MAXPRICE]).price));
		}
		if (strcmp(token, "-MinimumNumRooms") == 0)
		{
			sscanf(strtok(NULL, seps), "%d", &((arr[MINROOM]).numRooms));
		}
		if (strcmp(token, "-MaximumNumRooms") == 0)
		{
			sscanf(strtok(NULL, seps), "%d", &((arr[MAXROOM]).numRooms));
		}
		if (strcmp(token, "-Date") == 0)
		{
			sscanf(strtok(NULL, seps), "%d", &(numDate));
			arr[DATE].entrenceDate = numToDate(numDate);
		}
		if (strcmp(token, "-Enter") == 0)
		{
			sscanf(strtok(NULL, seps), "%d", &((arr[ENTER]).code));
		}
		if (strcmp(token, "-sr") == 0)
		{
			arr[SORT].code = 1;
		}
		if (strcmp(token, "-s") == 0)
		{
			arr[SORT].code = -1;
		}
		token = strtok(NULL, seps);
	}
	searchTheApartments(lst, arr);
}

void add_an_apt(APlist *lst, char *string, int *serialNum)/*get apartment input*/
{
	char *token;
	char *adress;
	int price, code;
	int numRooms;
	short int numRoomss;
	int entrenceDated, entrenceDatem, entrenceDatey;
	Date entrenceDate;
	char *seps = "\"";

	token = strtok(string, seps);
	adress = token;
	seps = " ";

	token = strtok(NULL, seps);
	sscanf(token, "%d", &price);

	token = strtok(NULL, seps);
	sscanf(token, "%d", &numRooms);
	numRoomss = (short int)numRooms;
	code = *serialNum;
	(*serialNum)++;

	token = strtok(NULL, seps);
	sscanf(token, "%d", &entrenceDated);
	entrenceDate.day = (short int)entrenceDated;

	token = strtok(NULL, seps);
	sscanf(token, "%d", &entrenceDatem);
	entrenceDate.month = (short int)entrenceDatem;

	token = strtok(NULL, seps);
	sscanf(token, "%d", &entrenceDatey);
	entrenceDate.year = (short int)entrenceDatey;

	insertData1ToEndList(lst, code, adress, price, numRoomss, entrenceDate);

}

void buy_an_apt(APlist *lst, char *code, int *serialNum)/*delete 1 apartmen from memory*/
{
	APnode* prev = lst->head;
	APnode *curr = prev->next;
	int coden;
	sscanf(code, "%d", &coden);
	if (lst->head->Ap.code == coden)
	{
		curr = lst->head;
		lst->head = lst->head->next;
		free(curr->Ap.adress);
		free(curr);
		if (lst->head == NULL)
			lst->tail = NULL;
	}
	else
	{
		while (curr != NULL)
		{
			if (curr->Ap.code == coden)
			{
				prev->next = curr->next;
				free(curr->Ap.adress);
				free(curr);
				if (prev->next == NULL)
					lst->tail = prev;
				break;
			}
			curr = curr->next;
			prev = prev->next;
		}
	}
	if (lst->tail != NULL)
		*serialNum = lst->tail->Ap.code + 1;
	else
		*serialNum = 1;
}

void delete_an_apt(APlist *lst, char *num, int *serialNum)/*delete several apartments from memory*/
{

	APnode *curr, *save = lst->head, *prev = lst->head;
	int num1;
	sscanf(num, "%d", &num1);
	while ((lst->head != NULL) && enterdinlastdays(lst->head->eTime, num1)) 
	{
		save = lst->head->next;
		free(lst->head->Ap.adress);
		free(lst->head);
		lst->head = save;
		if (save == NULL)
		{
			lst->tail = NULL;
			*serialNum = 1;
			return;
		}
	}
	curr = save;
	while (curr != NULL&&curr->next != NULL)
	{
		if (enterdinlastdays(curr->next->eTime, num1))
		{
			save = curr->next->next;
			free(curr->next->Ap.adress);
			free(curr->next);
			curr->next = save;
		}
		if (curr->next == NULL)
		{
			lst->tail = curr;
		}
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL&&curr->next == NULL&& enterdinlastdays(curr->eTime, num1))
	{
		lst->tail = prev;
		free(curr->Ap.adress);
		free(curr);
		prev->next = NULL;
	}
	if (lst->tail != NULL)
		*serialNum = lst->tail->Ap.code + 1;
	else
		*serialNum = 1;
}

void docommand(char *command, APlist *list, int *serialNum)/*send command from program back to the start to re do it*/
{
	char *token;
	char *seps = " ";
	token = strtok(command, seps);
	if (strcmp(token, "get-an-apt") == 0)
	{
		token = strtok(NULL, "\0");
		get_an_apt(token, *list);
	}

	else if (strcmp(token, "add-an-apt") == 0)
	{
		token = strtok(NULL, "\0");
		add_an_apt(list, token, serialNum);
	}

	else if (strcmp(token, "buy-an-apt") == 0)
	{
		token = strtok(NULL, seps);
		buy_an_apt(list, token, serialNum);
	}

	else if (strcmp(token, "delete-an-apt") == 0)
	{
		token = strtok(NULL, seps);
		delete_an_apt(list, token, serialNum);
	}
}

char* getcommandbynum(char* command, char *arr[N], CList commandList, int shortermsize, int longtermsize)/*re do command with specific number with needed changes*/
{
	char* fixedcommand = strdup(command + 1);
	char *seps = "^";
	char* token;
	char *pointer, *restOfString;
	char *str1, *str2;
	int numcommand, i = 1, newlen;
	char* savecommand, *tempcommand;
	token = strtok(fixedcommand, seps);
	sscanf(token, "%d", &numcommand);
	token = strtok(NULL, seps);
	CLNode *curr = commandList.head;
	if (longtermsize == 0)
	{
		savecommand = strdup(arr[numcommand - 1]);
	}
	else
	{
		if (numcommand > longtermsize)
		{
			savecommand = strdup(arr[numcommand - longtermsize - 1]);
		}
		else
		{
			while (i < numcommand)
			{
				curr = curr->next;
				i++;
			}
			savecommand = strdup(curr->command);
		}
	}
	if (token == NULL)/*only number*/
	{
		return savecommand;
	}
	else/*withstrings*/
	{
		i = 0;
		tempcommand = strdup(savecommand);
		str1 = strdup(token);
		token = strtok(NULL, seps);
		str2 = strdup(token);
		newlen = strlen(str2);
		pointer = strstr(tempcommand, str1);
		while (pointer != NULL)
		{
			restOfString = strdup(pointer + strlen(str1));
			savecommand = (char*)realloc(savecommand, strlen(savecommand) - strlen(str1) + strlen(str2) + 1);
			str2 = (char*)realloc(str2, strlen(str2) + strlen(restOfString) + 1);
			strcat(str2, restOfString);
			strncpy(savecommand+(pointer-tempcommand)+(strlen(token)-strlen(str1))*i, str2, strlen(str2) + 1);
			free(str2);
			free(restOfString);
			pointer = strstr(pointer+1, str1);
			str2 = strdup(token);
			i++;
		}
		free(str2);
		free(fixedcommand);
		free(str1);
		free(tempcommand);
		return savecommand;
	}
}

void mainCommand(APlist *list, CList *oldCommandList, char  *short_term_history[N], int *serialNum ,int * shortTermSize ,int* longtermsize)/*where all begins :)*/
{
	char *command, *commandM, *token, *seps = " ";
	command = getcommand();
	commandM = strdup(command);
	bool flag;

	if (command[0] != '!')
		token = strtok(command, seps);
	else
		token = command;

	while (strcmp(token, "exit") != 0)
	{
		flag = false;
		if (token != NULL)
		{
			if (strcmp(token, "get-an-apt") == 0)
			{
				token = strtok(NULL, "\0");
				get_an_apt(token, *list);
				flag = true;
			}
			else if (strcmp(token, "add-an-apt") == 0)
			{
				token = strtok(NULL, "\0");
				add_an_apt(list, token, serialNum);
				flag = true;
			}
			else if (strcmp(token, "buy-an-apt") == 0)
			{
				token = strtok(NULL, seps);
				buy_an_apt(list, token, serialNum);
				flag = true;
			}
			else if (strcmp(token, "delete-an-apt") == 0)
			{
				token = strtok(NULL, seps);
				delete_an_apt(list, token, serialNum);
				flag = true;
			}
			else if (strcmp(token, "!!") == 0)
			{
				free(command);
				command = strdup(short_term_history[*shortTermSize - 1]);
				docommand(command, list, serialNum);
				free(commandM);
				commandM = strdup(short_term_history[*shortTermSize - 1]);
				flag = true;
			}
			else if (token[0] == '!')
			{
				free(commandM);
				commandM = getcommandbynum(token, short_term_history, *oldCommandList, *shortTermSize, *longtermsize);
				free(command);
				command = strdup(commandM);
				docommand(command, list, serialNum);
				flag = true;
			}
			else if (strcmp(token, "short_history") == 0)
			{
				printShortHistory(short_term_history, *shortTermSize, *longtermsize);
			}

			else if (strcmp(token, "history") == 0)
			{
				printHistory(short_term_history, *oldCommandList, *shortTermSize, *longtermsize);
			}

			else
				printf("wrong command\n");
		}
		free(command);
		if (flag)
			putinmemory(commandM, short_term_history, oldCommandList, shortTermSize, longtermsize);
		free(commandM);
		printf(">>");
		command = getcommand();
		commandM = strdup(command);
		if (command[0] != '!')
			token = strtok(command, seps);
		else
			token = command;
	}
}