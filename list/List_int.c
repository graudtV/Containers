#include "List_int.h"
#include "List_generic.h"
#include <stdlib.h>
#include <assert.h>

void cpyInt(void *dst, const void *src)
{
	//*((int *) dst) = *((int *) src);
	printf("cpyInt\n");
}

List_int *_newList_int()
{
	List_ *list = _newCustomList(sizeof(int), cpyInt, NULL, NULL);
	return (List_int *) list;
}
