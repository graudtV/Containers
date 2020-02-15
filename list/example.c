#include "List.h"

void printCharFunc(void *data)
{
	printf("%c", *(char *) data);
}

void cpyChar(void *dst, const void *src)
{
	*((char *) dst) = *((char *) src);
}

int main()
{
	List *list = newCustomList(char, cpyChar, NULL, NULL);
	
	char str[] = "Hello, world!!!";
	for (int i = 0; str[i]; ++i)
		listPushFront(list, &str[i]);	

	listReverse(list);
	listWalk(list, printCharFunc);
	printf("\n");
	
	listDestroy(list);
	return 0;
}