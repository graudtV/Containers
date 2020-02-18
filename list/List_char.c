#include "List_char.h"
#include "List_generic.h"

static void cpy_char(void *dst, const void *src)
{
	*((char *) dst) = *((char *) src);
}

static int cmp_char(const void *arg1, const void *arg2)
{
	return (*(char *) arg1) - (*(char *) arg2);
}

List_char *_newList_char()
{
	GList *list = _newCustomList(sizeof(char), cpy_char, cmp_char, NULL); //free function is not needed - no allocation
	return (List_char *) list;
}

void _listPushFront_char(List_char *list, char val)
{
	glistPushFront((GList *) list, &val);
}

char _listPopFront_char(List_char *list)
{
	char return_value = *(char *) glistFront((GList *) list);
	glistPopFront((GList *) list);
	return return_value;
}