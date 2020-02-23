#ifndef _LISTCHAR_H_
#define _LISTCHAR_H_

#include "List_generic.h" //для struct List

typedef struct {} List_char;

List_char *_newList_char();
void _listPushFront_char(List_char *list, char val);
char _listPopFront_char(List_char *list);
int *_listFind_char(List_char *list, char val); //возвращает int *, а не char *, т.к. иначе не будет отличима от строки
void _listSpliceAfter_char(char *itPos, List_char *otherList);

#endif // _LISTCHAR_H_