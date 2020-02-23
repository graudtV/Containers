#ifndef _LISTINT_H_
#define _LISTINT_H_

#include "List_generic.h" //для struct List

typedef struct {} List_int;

List_int *_newList_int();
void _listPushFront_int(List_int *list, int val);
int _listPopFront_int(List_int *list);
void _listSpliceAfter_int(int *itPos, List_int *otherList);

#endif // _LISTINT_H_