#include "List.h"
#include <stdlib.h>
#include <assert.h>


void cpyFunc(void *dst, const void *src)
{
	*((int *) dst) = *((int *) src);
	printf("cpyChar\n");
}

int main()
{
	List (int) *list = newList(int);
	List (custom) *glist = newCustomList(char, cpyFunc, NULL, NULL);


	listPushFront(list, 5);
//	listPopFront(list);

	char ch = 'a';
	listPushFront(glist, &ch);
	//listPopFront(glist);

	int val = listFront(list);
	listFront(list) = 228;
	printf("%d\n", listFront(list));

	char *ptr = listFront(glist);
	printf("%c\n", *ptr);

	listReverse(list);
	listReverse(glist);

	listEmpty(list);
	listEmpty(glist);

	listClear(list);
	listClear(glist);

	listDestroy(glist);
	listDestroy(list);

	return 0;
}