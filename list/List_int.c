#include "List_int.h"
#include "List_generic.h"

static void cpy_int(void *dst, const void *src)
{
	*((int *) dst) = *((int *) src);
}

static int cmp_int(const void *arg1, const void *arg2)
{
	return (*(int *) arg1) - (*(int *) arg2);
}

List_int *_newList_int()
{
	GList *list = _newCustomList(sizeof(int), cpy_int, cmp_int, NULL); //free function is not needed - no allocation
	return (List_int *) list;
}

void _listPushFront_int(List_int *list, int val)
{
	glistPushFront((GList *) list, &val); //благодаря функции создана локальная переменная val, её адрес и можем передать
}

int _listPopFront_int(List_int *list)
{
	int return_value = *(int *) glistFront((GList *) list);
	glistPopFront((GList *) list);
	return return_value;
}

int *_listFind_int(List_int *list, int val)
{
	return (int *) glistFind((GList *) list, &val);
}

void _listSpliceAfter_int(int *itPos, List_int *otherList)
{
	glistSpliceAfter((void *) itPos, (GList *) otherList);
}