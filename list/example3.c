#include "List.h"
#include <stdlib.h>
#include <assert.h>

int main()
{
	ListInt *list = newList(int);

	List *l = &list->glist;
	printf("list = %p\n", list);
	printf("glist = %p\n", l);
	//printf("%zu %zu\n", sizeof(List), sizeof(ListInt));
	printf("glist->head = %p\n", l->head);
	printf("glist->data_sz = %zu\n", l->data_sz);
	printf("glist->cpy = %p\n", l->cpy);
	printf("glist->cmp = %p\n", l->cmp);
	printf("glist->free = %p\n", l->free);
	int a = 1;
	//calloc(1, sizeof(void *) + l->data_sz);
	_listPushFront(l, &a);
	++a;
	listPushFront(l, &a);
	++a;
	listPushFront(l, &a);

	//listPushFront(l, 2);
	printf("ready to destroy\n");
	listDestroy(list);
	return 0;
}