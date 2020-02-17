#include "List.h"
#include <string.h>
#include <stdlib.h>
void cpyStr(void *dst, const void *src)
{
	*(char **) dst = strdup((char *) src);
}

void freeStr(void *str)
{
	free(str);
}

void printStr(void *ppstr)
{
	printf("%s", *(char **) ppstr);
}

int main()
{
	List *list = newCustomList(char *, cpyStr, NULL, freeStr);

	listPushFront(list, "abc\n");
	listPushFront(list, "Hello, world!\n");
	listPushFront(list, "Have a nice day!\n");
	listPushFront(list, "def\n");

	listPopFront(list); //"def" удалится
	listReverse(list);
	listPopFront(list); //"abc" удалится

	listWalk(list, printStr); //печатаем содержимое списка

	listDestroy(list);

	return 0;
}