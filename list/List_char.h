#ifndef _LISTCHAR_H_
#define _LISTCHAR_H_

#include "List_generic.h" //для struct List

typedef struct {} List_char;

List_char *_newList_char();
void _listPushFront_char(List_char *list, char val);
char _listPopFront_char(List_char *list);
void _listSpliceAfter_char(char *itPos, List_char *otherList);

#endif // _LISTCHAR_H_