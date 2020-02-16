#include "List_int.h"
#include <stdlib.h>
#include <assert.h>

void cpyInt(void *dst, const void *src)
{
	//*((int *) dst) = *((int *) src);
	printf("cpyInt\n");
}

ListInt *_newIntList()
{
	void _listInit(List *list, size_t dataSize, void (*cpyFunc)(void *dst, const void *src),
					void (*cmpFunc)(const void *arg1, const void *arg2), void (*freeFunc)(void *data) ); //defined in list_generic.c
	
	ListInt *list = calloc(1, sizeof(List));
	assert(list != NULL);

	_listInit(&list->glist, sizeof(int), cpyInt, NULL, NULL);

	return list;
}

void _listIntDestroy(ListInt *list)
{
	_listDestroy(&list->glist); // <=> &(list->glist)
	//listDestroy автоматически делает free для переданного указателя, т.е. она сделает это для &list->glist, который совпадает с адресом list. (В структуре ListInt единственный элемент glist). Поэтому вызов free(list) будет лишним - дважды освободится одна и та же память
	printf("destroy ListInt\n");
}