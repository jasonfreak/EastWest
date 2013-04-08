/****************************************************************/
/* ÎÄ¼þÃû£º	EastWest.c					*/
/* ¹¦ÄÜ£º	ÖÕ¶ËGUI						*/
/* ×÷Õß£º	zengcx@hundsun.com				*/
/* Ê±¼ä£º	2011-06-20					*/
/****************************************************************/
#include"EastWest.h"
static xmlNodePtr EW_GetNext(xmlNodePtr Node)
{
	Node = Node->next;
	while(NULL != Node)
	{
		if(NULL != xmlGetProp(Node, (const xmlChar *)EW_ID))
		{
			break;
		}
		Node = Node->next;
	}
	
	return Node;
}

static xmlNodePtr EW_GetPrev(xmlNodePtr Node)
{
	Node = Node->prev;
	while(NULL != Node)
	{
		if(NULL != xmlGetProp(Node, (const xmlChar *)EW_ID))
		{
			break;
		}
		Node = Node->prev;
	}
	
	return Node;
}

static xmlNodePtr EW_GetChild(xmlNodePtr Node)
{
	if(NULL != Node)
	{
		Node = Node->children;
		while(NULL != Node)
		{
			if(NULL != xmlGetProp(Node, (const xmlChar *)EW_ID))
			{
				break;
			}
			Node = Node->next;
		}
	}
	return Node;
}

static xmlNodePtr EW_GetParent(xmlNodePtr Node)
{
	if(NULL != Node)
	{
		Node = Node->parent;
	}
	return Node;
}

static char *EW_GetId(xmlNodePtr Node)
{
	return (char *)xmlGetProp(Node, (const xmlChar *)EW_ID);
}

static EW_EntPtr EW_GetLink(xmlNodePtr Node)
{
	EW_EntPtr EntPtr;
	char *Link = (char *)xmlGetProp(Node, (const xmlChar *)EW_LINK);
	if(NULL == Link)
	{
		return NULL;
	}
	else
	{
		EntPtr = (EW_EntPtr)atol(Link);
		return EntPtr;
	}
}

static int EW_GetSizeX(xmlNodePtr Node)
{
	char *SizeX = (char *)xmlGetProp(Node, (const xmlChar *)EW_SIZEX);
	if(NULL == SizeX)
	{
		return -1;
	}
	else
	{
		return atoi(SizeX);
	}
}

static int EW_GetSizeY(xmlNodePtr Node)
{
	char *SizeY = (char *)xmlGetProp(Node, (const xmlChar *)EW_SIZEY);
	if(NULL == SizeY)
	{
		return -1;
	}
	else
	{
		return atoi(SizeY);
	}
}

static int EW_GetPosX(xmlNodePtr Node)
{
	char *PosX = (char *)xmlGetProp(Node, (const xmlChar *)EW_POSX);
	if(NULL == PosX)
	{
		return -1;
	}
	else
	{
		return atoi(PosX);
	}
}

static int EW_GetPosY(xmlNodePtr Node)
{
	char *PosY = (char *)xmlGetProp(Node, (const xmlChar *)EW_POSY);
	if(NULL == PosY)
	{
		return -1;
	}
	else
	{
		return atoi(PosY);
	}
}

static char *EW_GetValue(xmlNodePtr Node)
{
	xmlNodePtr Child;
	
	Child = Node->children;
	while(NULL != Child)
	{
		if(0 == xmlStrcmp(Child->name, (const xmlChar *)EW_VALUE))
		{
			break;
		}
		else
		{
			Child = Child->next;
		}
	}
	if(NULL == Child)
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]point[%s]", __FILE__, __LINE__, (char *)Node->name);
		return NULL;
	}
	
	
	return (char *)xmlNodeGetContent(Child);
}

static int EW_GetUse(xmlNodePtr Node)
{
	char *Use = (char *)xmlGetProp(Node, (const xmlChar *)EW_USE);
	if(NULL == Use)
	{
		return -1;
	}
	else
	{
		return atol(Use);
	}
}

static char* EW_GetState(xmlDocPtr Doc)
{
	xmlNodePtr Root;
	xmlNodePtr Father;
	
	Root = xmlDocGetRootElement(Doc);
	Father = Root->children;
	while(NULL != Father)
	{
		if(0 == xmlStrcmp(Father->name, (const xmlChar *)EW_STATE))
		{
			break;
		}
		else
		{
			Father = Father->next;
		}
	}
	if(NULL == Father)
	{
		return NULL;
	}
	
	return (char *)xmlNodeGetContent(Father);
	
}

static char* EW_GetLib(xmlDocPtr Doc)
{
	xmlNodePtr Root;
	xmlNodePtr Father;
	
	Root = xmlDocGetRootElement(Doc);
	Father = Root->children;
	while(NULL != Father)
	{
		if(0 == xmlStrcmp(Father->name, (const xmlChar *)EW_LIB))
		{
			break;
		}
		else
		{
			Father = Father->next;
		}
	}
	if(NULL == Father)
	{
		return NULL;
	}
	
	return (char *)xmlNodeGetContent(Father);
	
}

static int EW_SetLink(xmlNodePtr Node, EW_EntPtr EntPtr)
{
	char Temp[16];
	
	if(NULL == EntPtr)
	{
		return -1;
	}
	
	memset(Temp, 0x00, sizeof(Temp));
	sprintf(Temp, "%d", (long)EntPtr);
	
	if(NULL == xmlSetProp(Node, (const xmlChar *)EW_LINK, (const xmlChar *)Temp))
	{
		return -1;
	}
	
	return 0;
}

static int EW_SetSizeX(xmlNodePtr Node, int SizeX)
{
	char Temp[8];
	
	if(0 < SizeX)
	{
		return -1;
	}
	
	memset(Temp, 0x00, sizeof(Temp));
	sprintf(Temp, "%d", SizeX);
	
	if(NULL == xmlSetProp(Node, (const xmlChar *)EW_SIZEX, (const xmlChar *)Temp))
	{
		return -1;
	}
	
	return 0;
}

static int EW_SetSizeY(xmlNodePtr Node, int SizeY)
{
	char Temp[8];
	
	if(0 < SizeY)
	{
		return -1;
	}
	
	memset(Temp, 0x00, sizeof(Temp));
	sprintf(Temp, "%d", SizeY);
	
	if(NULL == xmlSetProp(Node, (const xmlChar *)EW_SIZEY, (const xmlChar *)Temp))
	{
		return -1;
	}
	
	return 0;
}

static int EW_SetPosX(xmlNodePtr Node, int PosX)
{
	char Temp[8];
	
	if(0 < PosX)
	{
		return -1;
	}
	
	memset(Temp, 0x00, sizeof(Temp));
	sprintf(Temp, "%d", PosX);
	
	if(NULL == xmlSetProp(Node, (const xmlChar *)EW_POSX, (const xmlChar *)Temp))
	{
		return -1;
	}
	
	return 0;
}

static int EW_SetPosY(xmlNodePtr Node, int PosY)
{
	char Temp[8];
	
	if(0 < PosY)
	{
		return -1;
	}
	
	memset(Temp, 0x00, sizeof(Temp));
	sprintf(Temp, "%d", PosY);
	
	if(NULL == xmlSetProp(Node, (const xmlChar *)EW_POSY, (const xmlChar *)Temp))
	{
		return -1;
	}
	
	return 0;
}

int EW_SetValue(xmlNodePtr Node, char *Value)
{
	xmlNodePtr Child;
	
	if(NULL == Value)
	{
		return -1;
	}
	
	Child = Node->children;
	while(NULL != Child)
	{
		if(0 == xmlStrcmp(Child->name, (const xmlChar *)EW_VALUE))
		{
			break;
		}
		else
		{
			Child = Child->next;
		}
	}
	if(NULL == Child)
	{
		return -1;
	}
	
	xmlNodeSetContent(Child, (const xmlChar *)Value);
	return 0;
}

static int EW_SetUse(xmlNodePtr Node, int Use)
{
	char Temp[8];
	
	if(0 > Use)
	{
		return -1;
	}
	
	memset(Temp, 0x00, sizeof(Temp));
	sprintf(Temp, "%d", Use);
	
	if(NULL == xmlSetProp(Node, (const xmlChar *)EW_USE, (const xmlChar *)Temp))
	{
		return -1;
	}
	
	return 0;
}

int EW_SetState(xmlDocPtr Doc, char *State)
{
	xmlNodePtr Root;
	xmlNodePtr Father;
	
	if(NULL == State)
	{
		return -1;
	}
	
	Root = xmlDocGetRootElement(Doc);
	Father = Root->children;
	while(NULL != Father)
	{
		if(0 == xmlStrcmp(Father->name, (const xmlChar *)EW_STATE))
		{
			break;
		}
		else
		{
			Father = Father->next;
		}
	}
	if(NULL == Father)
	{
		return -1;
	}
	
	xmlNodeSetContent(Father, (const xmlChar *)State);
	return 0;
}

static void EW_DisSelf(xmlDocPtr Doc, xmlNodePtr Node)
{
	EW_EntPtr EntPtr;
	
	while(NULL != Node)
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]³¢ÊÔÏÔÊ¾»¯Óò[%s]", __FILE__, __LINE__, (char *)Node->name);
		if(NULL != (EntPtr = EW_GetLink(Node)))
		{
			EntPtr->EW_Dis(Doc, Node, EW_GetUse(Node));
		}
		else
		{
			WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÁ´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		}
		
		EW_DisSelf(Doc, EW_GetChild(Node));
		Node = EW_GetNext(Node);
	}
}

void EW_DisAll(xmlDocPtr Doc)
{
	xmlNodePtr Root;
	xmlNodePtr Father;
	EW_EntPtr EntPtr;
	
	Root = xmlDocGetRootElement(Doc);
	Father = Root->children;
	while(NULL != Father)
	{
		if(0 == xmlStrcmp(Father->name, (const xmlChar *)EW_WINDOW))
		{
			break;
		}
		else
		{
			Father = Father->next;
		}
	}
	if(NULL == Father)
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]È±ÉÙÓò[%s]", __FILE__, __LINE__, EW_WINDOW);
		return;
	}
	

	EW_DisSelf(Doc, Father);
}

static int EW_NewWin(xmlDocPtr Doc, xmlNodePtr Node)
{
	int SizeX;
	int SizeY;
	int PosX;
	int PosY;
	EW_EntPtr EntPtr;
	if(0 > (SizeX = EW_GetSizeX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	if(0 > (SizeY = EW_GetSizeY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	if(0 > (PosX = EW_GetPosX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	if(0 > (PosY = EW_GetPosY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]³ß´ç=[%d * %d]×ø±ê=[%d * %d]", __FILE__, __LINE__, (char *)Node->name, SizeX, SizeY, PosX, PosY);
	EntPtr = (EW_EntPtr)malloc(sizeof(struct EW_Entity));
	EntPtr->Win = newwin(SizeY, SizeX, PosY, PosX);
	EntPtr->EW_New = &EW_NewWin;
	EntPtr->EW_Del = &EW_DelWin;
	EntPtr->EW_On = &EW_OnWin;
	EntPtr->EW_Dis = &EW_DisWin;
	
	if(0 > EW_SetLink(Node, EntPtr))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]Ð´Á´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	
	return 0;
}

static int EW_DelWin(xmlDocPtr Doc, xmlNodePtr Node)
{
	EW_EntPtr EntPtr;
	
	if(NULL == (EntPtr = EW_GetLink(Node)))
	{
		return -1;
	}
	
	delwin(EntPtr->Win);
	free(EntPtr);
	return 0;
}

static int EW_OnWin(xmlDocPtr Doc, xmlNodePtr Node)
{
	EW_EntPtr EntPtr;
	int Action;
	
	if(0 > EW_SetState(Doc, EW_WINDOW))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]Ð´×´Ì¬´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	EW_DisAll(Doc);
	
	if(NULL == (EntPtr = EW_GetLink(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÁ´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	wmove(EntPtr->Win, 1, 1);
	wrefresh(EntPtr->Win);
	
	while(1)
	{
		Action = getch();
		switch(Action)
		{
			case EW_ESC:
				return EW_UP;
			case EW_ENTER:
				return EW_DOWN;
			default:
				break;
		}
	}
}

static void EW_DisWin(xmlDocPtr Doc, xmlNodePtr Node, int Flag)
{
	int SizeX;
	int SizeY;
	int PosX;
	int PosY;
	char *Value;
	char *State;
	EW_EntPtr EntPtr;
	
	if(0 > (SizeX = EW_GetSizeX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	if(0 > (SizeY = EW_GetSizeY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	if(0 > (PosX = EW_GetPosX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	if(0 > (PosY = EW_GetPosY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	if(NULL == (EntPtr = EW_GetLink(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÁ´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}

	if(NULL == (Value = EW_GetValue(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÖµ´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	if(NULL == (State = EW_GetState(Doc)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶Á×´Ì¬´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	if(EW_DIS == Flag || EW_FUC == Flag)
	{
		wclear(EntPtr->Win);
		wattrset(EntPtr->Win, A_NORMAL);
		box(EntPtr->Win, ACS_VLINE, ACS_HLINE);
		wattron(EntPtr->Win, A_BOLD);
		mvwaddnstr(EntPtr->Win, 1, 1, Value, SizeX-2);
		wattroff(EntPtr->Win, A_BOLD);
		mvwhline(EntPtr->Win, 2, 1, ACS_HLINE, SizeX-2);
		mvwhline(EntPtr->Win, SizeY-3, 1, ACS_HLINE, SizeX-2);
		wattron(EntPtr->Win, A_BLINK);
		mvwaddnstr(EntPtr->Win, SizeY-2, 1, State, SizeX-2);
		wattroff(EntPtr->Win, A_BLINK);
		wmove(EntPtr->Win, SizeY-2, 1);
		
		
		wrefresh(EntPtr->Win);
	}
	else
	{
		wclear(EntPtr->Win);
		wrefresh(EntPtr->Win);
	}
	
}

static int EW_NewBut(xmlDocPtr Doc, xmlNodePtr Node)
{
	int SizeX;
	int SizeY;
	int PosX;
	int PosY;
	EW_EntPtr EntPtr;
	if(0 > (SizeX = EW_GetSizeX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	if(0 > (SizeY = EW_GetSizeY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	if(0 > (PosX = EW_GetPosX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	if(0 > (PosY = EW_GetPosY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]³ß´ç=[%d * %d]×ø±ê=[%d * %d]", __FILE__, __LINE__, (char *)Node->name, SizeX, SizeY, PosX, PosY);
	EntPtr = (EW_EntPtr)malloc(sizeof(struct EW_Entity));
	EntPtr->Win = newwin(SizeY, SizeX, PosY, PosX);
	EntPtr->EW_New = &EW_NewBut;
	EntPtr->EW_Del = &EW_DelBut;
	EntPtr->EW_On = &EW_OnBut;
	EntPtr->EW_Dis = &EW_DisBut;
	
	if(0 > EW_SetLink(Node, EntPtr))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]Ð´Á´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	
	return 0;
}

static int EW_DelBut(xmlDocPtr Doc, xmlNodePtr Node)
{
	EW_EntPtr EntPtr;
	
	if(NULL == (EntPtr = EW_GetLink(Node)))
	{
		return -1;
	}
	
	delwin(EntPtr->Win);
	free(EntPtr);
	return 0;
}

static int EW_OnBut(xmlDocPtr Doc, xmlNodePtr Node)
{
	EW_EntPtr EntPtr;
	int Action;
	char *Lib;
	char *Id;
	char DlName[256];
	void *Handle;
	
	if(0 > EW_SetState(Doc, EW_BUTTON))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]Ð´×´Ì¬´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	EW_DisAll(Doc);
	
	if(NULL == (EntPtr = EW_GetLink(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÁ´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	wmove(EntPtr->Win, 1, 1);
	wrefresh(EntPtr->Win);
	
	if(NULL == (Lib = EW_GetLib(Doc)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶Á¿â´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	
	if(NULL == (Id = EW_GetId(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÉí·Ý´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return -1;
	}
	
	while(1)
	{
		Action = getch();
		switch(Action)
		{
			case EW_ESC:
				return EW_UP;
			case EW_ENTER:
				if(NULL != (Handle = dlopen(Lib, RTLD_LAZY)))
				{
					memset(DlName, 0x00, sizeof(DlName));
					sprintf(DlName, "EW_%s_ENTER", Id);
					if(NULL != (EW_ButEnter = (void (*)(xmlDocPtr, xmlNodePtr))dlsym(Handle, DlName)))
					{
						EW_ButEnter(Doc, Node);
					}
					else
					{
						WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶Áº¯Êý[%s]´íÎó", __FILE__, __LINE__, (char *)Node->name, DlName);	
					}
					dlclose(Handle);
				}
				else
				{
					WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶Á¿âÎÄ¼þ[%s]´íÎó", __FILE__, __LINE__, (char *)Node->name, Lib);
				}
				return EW_HOLD;
			case EW_FORWARD:
				return EW_NORTH;
			case EW_BACKWARD:
				return EW_SOUTH;
			case EW_LEFT:
				return EW_WEST;
			case EW_RIGHT:
				return EW_EAST;
			default:
				break;
		}
	}
}

static void EW_DisBut(xmlDocPtr Doc, xmlNodePtr Node, int Flag)
{
	int SizeX;
	int SizeY;
	int PosX;
	int PosY;
	char *Value;
	char Temp[256];
	char Fmt[256];
	EW_EntPtr EntPtr;
	
	if(0 > (SizeX = EW_GetSizeX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	if(0 > (SizeY = EW_GetSizeY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY³ß´ç´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	if(0 > (PosX = EW_GetPosX(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁX×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	if(0 > (PosY = EW_GetPosY(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁY×ø±ê´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	if(NULL == (EntPtr = EW_GetLink(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÁ´½Ó´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}

	if(NULL == (Value = EW_GetValue(Node)))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÖµ´íÎó", __FILE__, __LINE__, (char *)Node->name);
		return;
	}
	
	if(EW_DIS == Flag || EW_FUC == Flag)
	{
		wclear(EntPtr->Win);
		wattrset(EntPtr->Win, A_NORMAL);
		box(EntPtr->Win, ACS_VLINE, ACS_HLINE);
		memset(Fmt, 0x00, sizeof(Fmt));
		sprintf(Fmt, "%%-%d.%ds", SizeX-2, SizeX-2);
		memset(Temp, 0x00, sizeof(Temp));
		sprintf(Temp, Fmt, Value);
		if(EW_FUC == Flag)
		{
			wattron(EntPtr->Win, A_REVERSE);
		}
		mvwaddnstr(EntPtr->Win, 1, 1, Temp, SizeX-2);
		if(EW_FUC == Flag)
		{
			wattroff(EntPtr->Win, A_REVERSE);
		}
		wmove(EntPtr->Win, SizeY-2, 1);
		wrefresh(EntPtr->Win);
	}
	else
	{
		wclear(EntPtr->Win);
		wrefresh(EntPtr->Win);
	}
	
}

static int EW_Begin(xmlDocPtr Doc, xmlNodePtr Node)
{
	while(NULL != Node)
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]³¢ÊÔ³õÊ¼»¯Óò[%s]", __FILE__, __LINE__, (char *)Node->name);
		if(0 == xmlStrcmp(Node->name, (const xmlChar *)EW_WINDOW))
		{
			if(0 != EW_NewWin(Doc, Node))
			{
				WriteLog(LOGNAME, "[%-8.8s:%06.6d]³õÊ¼»¯Óò[%s]Ê§°Ü", __FILE__, __LINE__, (char *)Node->name);
				return -1;
			}
		}
		else if(0 == xmlStrcmp(Node->name, (const xmlChar *)EW_BUTTON))
		{
			if(0 != EW_NewBut(Doc, Node))
			{
				WriteLog(LOGNAME, "[%-8.8s:%06.6d]³õÊ¼»¯Óò[%s]Ê§°Ü", __FILE__, __LINE__, (char *)Node->name);
				return -1;
			}
		}
		
		EW_Begin(Doc, EW_GetChild(Node));
		Node = EW_GetNext(Node);
	}
	return 0;
}

static int EW_End(xmlDocPtr Doc, xmlNodePtr Node)
{
	while(NULL != Node)
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]³¢ÊÔ½áÊø»¯Óò[%s]", __FILE__, __LINE__, (char *)Node->name);
		if(0 == xmlStrcmp(Node->name, (const xmlChar *)EW_WINDOW))
		{
			if(0 != EW_DelWin(Doc, Node))
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		EW_End(Doc, EW_GetChild(Node));
		Node = EW_GetNext(Node);
	}
	return 0;
}

int EW_Run(xmlDocPtr Doc)
{
	int Destination;
	int Use;
	xmlNodePtr Root;
	xmlNodePtr Father;
	xmlNodePtr Current;
	EW_EntPtr EntPtr;
	
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]--------------Æ½Ì¨Æô¶¯--------------", __FILE__, __LINE__);
	
	Root = xmlDocGetRootElement(Doc);
	Father = Root->children;
	while(NULL != Father)
	{
		if(0 == xmlStrcmp(Father->name, (const xmlChar *)EW_WINDOW))
		{
			break;
		}
		else
		{
			Father = Father->next;
		}
	}
	if(NULL == Father)
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]È±ÉÙÓò[%s]", __FILE__, __LINE__, EW_WINDOW);
		return;
	}
	
	initscr();
	noecho();
	refresh();
	keypad(stdscr, true);
	if(0 != EW_Begin(Doc, Father))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]³õÊ¼»¯´íÎó", __FILE__, __LINE__);
		clear();
		refresh();
		if(0 != EW_End(Doc, Father))
		{
			WriteLog(LOGNAME, "[%-8.8s:%06.6d]½áÊø»¯´íÎó", __FILE__, __LINE__);
			return -1;
		}
		endwin();
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]½áÊø»¯³É¹¦", __FILE__, __LINE__);
		return -1;
	}
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]³õÊ¼»¯³É¹¦", __FILE__, __LINE__);	
	
	Current = Father;
	while(1)
	{
		if(NULL == (EntPtr = EW_GetLink(Current)))
		{
			WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÁ´½ÓÊ§°Ü", __FILE__, __LINE__, (char *)Current->name);
			goto END;
		}
		
		if(0 > (Use = EW_GetUse(Current)))
		{
			WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]¶ÁÓÃÍ¾Ê§°Ü", __FILE__, __LINE__, (char *)Current->name);
			goto END;
		}
		if(0 > EW_SetUse(Current, EW_FUC))
		{
			WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]Ð´ÓÃÍ¾Ê§°Ü", __FILE__, __LINE__, (char *)Current->name);
		}
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]½¹µã=[%s]", __FILE__, __LINE__, (char *)Current->name);
		Destination = EntPtr->EW_On(Doc, Current);
		if(0 > EW_SetUse(Current, Use))
		{
			WriteLog(LOGNAME, "[%-8.8s:%06.6d]Óò[%s]Ð´ÓÃÍ¾Ê§°Ü", __FILE__, __LINE__, (char *)Current->name);
			goto END;
		}
		switch(Destination)
		{
			case EW_EAST:
				if(NULL != EW_GetNext(Current))
				{
					Current = EW_GetNext(Current);
				}
				break;
			case EW_WEST:
				if(NULL != EW_GetPrev(Current))
				{
					Current = EW_GetPrev(Current);
				}
				break;
			case EW_NORTH:
				if(NULL != EW_GetNext(Current))
				{
					Current = EW_GetNext(Current);
				}
				break;
			case EW_SOUTH:
				if(NULL != EW_GetPrev(Current))
				{
					Current = EW_GetPrev(Current);
				}
				break;
			case EW_DOWN:
				if(NULL != EW_GetChild(Current))
				{
					Current = EW_GetChild(Current);
				}
				break;
			case EW_UP:
				Current = EW_GetParent(Current);
				if(0 == xmlStrcmp(Current->name, (const char *)EW_))
				{
					goto END;
				}
				break;
		}/*switch*/
	}/*while*/
	
END:
	clear();
	refresh();
	if(0 != EW_End(Doc, Father))
	{
		WriteLog(LOGNAME, "[%-8.8s:%06.6d]½áÊø»¯´íÎó", __FILE__, __LINE__);
		endwin();
		return -1;
	}
	endwin();
	WriteLog(LOGNAME, "[%-8.8s:%06.6d]½áÊø»¯³É¹¦", __FILE__, __LINE__);
	return 0;
}
