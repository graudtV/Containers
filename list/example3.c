#include "List.h"
#include <stdlib.h>
#include <assert.h>



int main()
{
	List (int) *list = newList(int);

	listPushFront(list, 10);
	listPushFront(list, 20);
	listPushFront(list, 30);

	printf("The front element is %d\n", listFront(list));
	listFront(list) = 228; //access to the first element
	printf("Now the front element is %d\n", listFront(list));

	listReverse(list);

	printf("Printing reversed list:\n");
	for (int i = 0; !listEmpty(list); ++i)
	{
		printf("%d. elem = %d\n", i + 1, listFront(list));
		listPopFront(list);
	}


	listDestroy(list);
	return 0;
}