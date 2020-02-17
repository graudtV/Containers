#include "List.h"
#include <stdlib.h>
#include <assert.h>


void cpyFunc(void *dst, const void *src)
{

}

int main()
{
	List (int) *list = newList(int);
	List () *glist = newCustomList(char, cpyFunc, NULL, NULL);

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