#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"EastWest.h"

void EW_But1_ENTER(xmlDocPtr Doc, xmlNodePtr Node)
{
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]域[%s]ENTER开始", __FILE__, __LINE__, (char *)Node->name);
	if(0 > EW_SetValue(Node, "test1"))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]域[%s]ENTER改变值错误", __FILE__, __LINE__, (char *)Node->name);
	}
	
	EW_DisAll(Doc);
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]域[%s]ENTER结束", __FILE__, __LINE__, (char *)Node->name);
}

void EW_But2_ENTER(xmlDocPtr Doc, xmlNodePtr Node)
{
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]域[%s]ENTER开始", __FILE__, __LINE__, (char *)Node->name);
	if(0 > EW_SetValue(Node, "test2"))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]域[%s]ENTER改变值错误", __FILE__, __LINE__, (char *)Node->name);
	}
	
	EW_DisAll(Doc);
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]域[%s]ENTER结束", __FILE__, __LINE__, (char *)Node->name);
}
