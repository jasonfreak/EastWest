/****************************************************************/
/* 文件名：	EastWest.h					*/
/* 功能：	终端GUI						*/
/* 作者：	zengcx@hundsun.com				*/
/* 时间：	2011-06-20					*/
/****************************************************************/
#ifndef EASTWEST_H
#define EASTWEST_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<libxml/xmlmemory.h>
#include<dlfcn.h>
#include"WriteLog.h"

#define LOGNAME "eastwest"

#define EW_ID "id"
#define EW_LINK "link"
#define EW_WINDOW "window"
#define EW_BUTTON "button"
#define EW_LABEL "label"
#define EW_TEXTBOX "textbox"
#define EW_SIZEX "sizex"
#define EW_SIZEY "sizey"
#define EW_POSX "posx"
#define EW_POSY "posy"
#define EW_VALUE "value"
#define EW_USE "use"
#define EW_STATE "state"
#define EW_LIB "lib"
#define EW_ "eastwest"

#define EW_HOLD -1
#define EW_EAST 0
#define EW_WEST 1
#define EW_NORTH 2
#define EW_SOUTH 3
#define EW_UP 4
#define EW_DOWN 5

#define EW_ESC 27
#define EW_ENTER '\n'
#define EW_FORWARD KEY_UP
#define EW_BACKWARD KEY_DOWN
#define EW_LEFT KEY_LEFT
#define EW_RIGHT KEY_RIGHT

#define EW_DIS 0
#define EW_FUC 1

typedef struct EW_Entity
{
        WINDOW *Win;
        int (*EW_New)(xmlDocPtr, xmlNodePtr);
        int (*EW_Del)(xmlDocPtr, xmlNodePtr);
	int (*EW_On)(xmlDocPtr, xmlNodePtr);
	void (*EW_Dis)(xmlDocPtr, xmlNodePtr, int);
} *EW_EntPtr;

static xmlNodePtr EW_GetNext(xmlNodePtr);
static xmlNodePtr EW_GetPrev(xmlNodePtr);
static xmlNodePtr EW_GetChild(xmlNodePtr);
static xmlNodePtr EW_GetParent(xmlNodePtr);

static char *EW_GetId(xmlNodePtr);
static EW_EntPtr EW_GetLink(xmlNodePtr);
static int EW_GetSizeX(xmlNodePtr);
static int EW_GetSizeY(xmlNodePtr);
static int EW_GetPosX(xmlNodePtr);
static int EW_GetPosY(xmlNodePtr);
static char *EW_GetValue(xmlNodePtr);
static int EW_SetLink(xmlNodePtr, EW_EntPtr);
static int EW_SetSizeX(xmlNodePtr, int);
static int EW_SetSizeY(xmlNodePtr, int);
static int EW_SetPosX(xmlNodePtr, int);
static int EW_SetPosY(xmlNodePtr, int);
int EW_SetValue(xmlNodePtr, char *);
static int EW_SetUse(xmlNodePtr , int );
int EW_SetState(xmlDocPtr , char *);

static void EW_DisSelf(xmlDocPtr, xmlNodePtr);
void EW_DisAll(xmlDocPtr);

static int EW_NewWin(xmlDocPtr, xmlNodePtr);
static int EW_DelWin(xmlDocPtr, xmlNodePtr);
static int EW_OnWin(xmlDocPtr, xmlNodePtr);
static void EW_DisWin(xmlDocPtr, xmlNodePtr, int);

static int EW_NewBut(xmlDocPtr, xmlNodePtr);
static int EW_DelBut(xmlDocPtr, xmlNodePtr);
static int EW_OnBut(xmlDocPtr, xmlNodePtr);
static void EW_DisBut(xmlDocPtr, xmlNodePtr, int);

static void (*EW_ButEnter)(xmlDocPtr, xmlNodePtr);

static int EW_Begin(xmlDocPtr, xmlNodePtr);
static int EW_End(xmlDocPtr, xmlNodePtr);
int EW_Run(xmlDocPtr);


#endif
