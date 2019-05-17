#include "MainHeader.h"

void main()
{
	int serialNum = 1, shortTermSize = 0, longtermsize = 0;
	char  *short_term_history[N];
	CList oldCommandList;
	APlist list;

	makeEmptyCList(&oldCommandList);/*reset data base*/
	makeEmptyList(&list);/*reset data base*/
	NullTheArray(short_term_history);/*reset data base*/

	printf("Please enter one of the following commands:\nadd-an-apt, get-an-apt, buy-an- apt or delete-an-apt\nFor reconstruction commands, please enter :\n!!, !num, history, short_history or !num^str1^str2\nTo exit, enter exit.\n");
	printf(">>");

	loadcommands(short_term_history, &shortTermSize, &oldCommandList, &longtermsize);/*load command from file*/
	loadapartments(&list, &serialNum);/*load apartments from file*/
	
	mainCommand(&list, &oldCommandList, short_term_history, &serialNum, &shortTermSize, &longtermsize);/*get commands from user*/

	savecommands(short_term_history, shortTermSize, oldCommandList, longtermsize);/*save command to file*/
	saveapartments(&list);/*save apartments to file*/

	freeAPList(&list);/*free memory*/
	freeCMList(&oldCommandList);/*free memory*/
	freeSCArr(short_term_history, shortTermSize);/*free memory*/

	printf("Good Bye!\n");
}
