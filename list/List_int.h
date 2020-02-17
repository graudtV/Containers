#ifndef _LISTINT_H_
#define _LISTINT_H_

#include "List_generic.h" //для struct List

typedef struct
{
	List glist; //generic list
} ListInt;

ListInt *_newIntList();

void _listIntDestroy(ListInt *list);

#endif // _LISTINT_H_