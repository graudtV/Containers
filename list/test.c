#include "List.h"
#include <string.h>
#include <stdlib.h>
void cpyStr(void *dst, const void *src)
{
	*(char **) dst = strdup((char *) src);
	//printf("new str '%s'", (char *) src);
	//printf("Allocated str %p, ptr written in %p\n", *(char **) dst, dst);
}

void freeStr(void *ppstr)
{
	free(*(char **) ppstr);
	//printf("Freing %p\n", *(char **) ppstr);
}

void printStr(void *ppstr)
{
	printf("%s", *(char **) ppstr);
}

int main()
{
	List *list = newCustomList(char *, cpyStr, NULL, freeStr);
	for (int j = 0; j < 1; ++j)
	{
		for (int i = 0; i < 10000000; ++i)
			listPushFront(list, "abcdef");
		listPopFront(list);
		listFront(list);
		listReverse(list);
		listClear(list);
		listReverse(list);
	}
	

	listDestroy(list);

	return 0;
}