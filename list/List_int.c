#include "List_int.h"
#include "List_generic.h"
#include <stdlib.h>
#include <assert.h>

static void cpy_int(void *dst, const void *src)
{
	*((int *) dst) = *((int *) src);
	printf("cpyInt\n");
}

static int cmp_int(const void *arg1, const void *arg2)
{
	return (*(int *) arg1) - (*(int *) arg2);
}

List_int *_newList_int()
{
	List_ *list = _newCustomList(sizeof(int), cpy_int, cmp_int, NULL); //free function is not needed - no allocation
	return (List_int *) list;
}

void _listPushFront_int(List_int *list, int val)
{
	_listPushFront((List_ *) list, &val);
}
