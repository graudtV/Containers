#include <forward_list>
#include <stdio.h>
int main()
{
	std::forward_list <int> lst = {1, 2, 3};
	lst.push_front(7);
	lst.resize(5);
	for (auto it = lst.begin(); it != lst.end(); ++it)
		printf("%d\n", *it);

	return 0;
}