#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"EastWest.h"

int main(int argc, char *argv[])
{
	char DocName[256];
	memset(DocName, 0x00, sizeof(DocName));
	sprintf(DocName, "%s.xml", argv[1]);
	
	xmlDocPtr Doc;
	if(NULL == (Doc = xmlParseFile(DocName)))
	{
		return -1;
	}
	
	if(0 != EW_Run(Doc))
	{
		xmlFreeDoc(Doc);
		return -1;
	} 
	else
	{
		xmlFreeDoc(Doc);
		return 0;
	}
}
