#include "List.h"

int main()
{
	char *message = "Hello, world!";
	List (char) *lst = newList(char);
	while (*message)
		listPushFront(lst, *(message++));

	listReverse(lst);
	while (!listEmpty(lst))
		printf("%c", listPopFront(lst));
	printf("\n");

	return 0;
}