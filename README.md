# Containers
Пробую реализовать list, stack, map с удобным интерфейсом на чистом C без всяких этих ваших там шаблонов

## List
### Пример использования
```C
List (int) *list = newList(int);

listPushFront(list, 10); //putting a value in the list
listFront(list) = 228; //access to the first element

listReverse(list);
listPopFront(list); //throwing a value from the list

listDestroy(list);
```
