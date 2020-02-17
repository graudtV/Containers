#include "List.h"
#include <string.h>
#include <stdlib.h>
void cpyStr(void *dst, const void *src)
{
	*(char **) dst = strdup((char *) src);
	printf("new str '%s'", (char *) src);
	printf("Allocated str %p, ptr written in %p\n", *(char **) dst, dst);
}

void freeStr(void *ppstr)
{
	free(*(char **) ppstr);
	printf("Freing %p\n", *(char **) ppstr);
}

void printStr(void *ppstr)
{
	printf("%s", *(char **) ppstr);
}

int main()
{
	List_ *list = newCustomList(char *, cpyStr, NULL, freeStr);
	printf("List size = %zu\n", sizeof(List_));
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