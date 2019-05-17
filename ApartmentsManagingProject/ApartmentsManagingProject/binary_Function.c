#include "MainHeader.h"

void saveapartments(APlist *lst)/*save apartments*/
{
	FILE* fbin;
	fbin = fopen("apartments.bin", "wb");
	assert(fbin!=NULL);
	APnode *curr = lst->head;
	short apcode, len;
	bits bit;
	while (curr != NULL)
	{
		apcode = (short)curr->Ap.code;
		fwrite(&apcode, sizeof(short), 1, fbin);
		len = strlen(curr->Ap.adress);
		fwrite(&len, sizeof(short), 1, fbin);
		fwrite(curr->Ap.adress, sizeof(char), len, fbin);
		fwrite(&(curr->Ap.price), sizeof(int), 1, fbin);
		bit = createbitsfromap(*curr);
		fwrite(&bit, sizeof(bits), 1, fbin);
		curr = curr->next;
	}
	fclose(fbin);
}

void loadapartments(APlist *lst, int *serialNum)/*load apartments*/
{
	makeEmptyList(lst);
	FILE *fbin = fopen("apartments.bin", "r+b");
	int len;
	short code;
	char* adress;
	short sizeAdress;
	APnode *temp;
	bits bit;
	if (fbin == NULL)
	{
		fbin = fopen("apartments.bin", "w+b");
	}
	else
	{
		fseek(fbin, 0, SEEK_END);
		len = (int)ftell(fbin);
		fseek(fbin, 0, SEEK_SET);
		while (ftell(fbin) < len)
		{
			temp = (APnode*)malloc(sizeof(APnode));
			fread(&(code), sizeof(short), 1, fbin);
			temp->Ap.code = code;
			fread(&(sizeAdress), sizeof(short), 1, fbin);
			adress = (char*)malloc(sizeof(char)*(sizeAdress + 1));
			fread(adress, sizeof(char), sizeAdress, fbin);
			temp->Ap.adress = adress;
			temp->Ap.adress[sizeAdress] = '\0';
			fread(&(temp->Ap.price), sizeof(int), 1, fbin);
			fread(&(bit), sizeof(bits), 1, fbin);
			createapfrombits(bit, &temp);
			insertNodeToEndList(lst, temp);
		}
		if(lst->tail!=NULL)
			(*serialNum) = lst->tail->Ap.code + 1;
	}
	fclose(fbin);
}

bits createbitsfromap(APnode ap)/*create bits from apartment*/
{
	BYTE daymask1 = 0x1E, daymask2 = 0x1, maskmonth = 0x0F, yearmask1 = 0x70, yearmask2 = 0xF0, emonth1 = 0x0E;
	BYTE temp;
	bits res;
	res.byte1 = ap.Ap.numRooms;
	res.byte1 = res.byte1 << 4;
	temp = (BYTE)ap.Ap.entrenceDate.day&daymask1;
	temp = temp >> 1;
	res.byte1 = res.byte1 | temp;
	res.byte2 = ((BYTE)ap.Ap.entrenceDate.day&daymask2) << 7;
	temp = (BYTE)ap.Ap.entrenceDate.month&maskmonth;
	res.byte2 = res.byte2 | (temp << 3);
	temp = (BYTE)ap.Ap.entrenceDate.year&yearmask1;
	temp = temp >> 4;
	res.byte2 = res.byte2 | temp;
	temp = (BYTE)ap.Ap.entrenceDate.year&yearmask2;
	res.byte3 = res.byte3 | (temp << 4);
	res.byte4 = (BYTE)(ap.eTime.day) << 3;
	temp = (BYTE)ap.eTime.month&emonth1;
	res.byte4 = res.byte4 | (temp >> 1);
	temp = (BYTE)ap.eTime.month & 0x01;
	res.byte5 = temp << 7;
	res.byte5 = res.byte5 | ((BYTE)ap.eTime.year & 0x7F);
	return res;
}

void createapfrombits(bits bit, APnode**res)/*convert bits to apartment struct*/
{
	(*res)->Ap.numRooms = ((bit.byte1 & 0xF0) >> 4);
	(*res)->Ap.entrenceDate.day = ((bit.byte1 & 0x0F) << 1);
	(*res)->Ap.entrenceDate.day = (((bit.byte2) & 0x80) >> 7) | (*res)->Ap.entrenceDate.day;
	(*res)->Ap.entrenceDate.month = (((bit.byte2) & 0x78) >> 3);
	(*res)->Ap.entrenceDate.year = (((bit.byte2) & 0x07) << 4);
	(*res)->Ap.entrenceDate.year = (*res)->Ap.entrenceDate.year | (((bit.byte3) & 0x0F) >> 4);
	(*res)->eTime.day = (((bit.byte4) & 0xF8) >> 3);
	(*res)->eTime.month = (((bit.byte4) & 0x07) << 1);
	(*res)->eTime.month = (*res)->eTime.month | (((bit.byte5) & 0x80) >> 7);
	(*res)->eTime.year = (((bit.byte5) & 0x7F));
}