#include "List.h"
#include <stdlib.h>
#include <assert.h>

List *_newCustomList(size_t dataSize, void (*cpyFunc)(void *dst, const void *src),
					void (*cmpFunc)(const void *arg1, const void *arg2), void (*freeFunc)(void *data) )
{
	assert(cpyFunc != NULL);	
	List *list = calloc(1, sizeof(List));
	assert(list != NULL);
	//Инициализация значениями
	list->head = NULL;
	list->data_sz = dataSize;
	list->cpy = cpyFunc;

	return list;
}

void _listDestroy(List *list)
{
	_listClear(list);

	list->data_sz = 0;
	list->cpy = NULL;
	list->cmp = NULL;
	list->free = NULL;

	free(list); //!!!
}



void _listPushFront(List *list, void *data)
{
	assert(list != NULL);
	assert(data != NULL);

	void *node = calloc(1, sizeof(void *) + list->data_sz);
	assert(node != NULL);
	//Инициализация нового элемента списка ("узла")
	*((void **) node) = list->head; //в поле next новой головы записываем указатель на старую
	list->cpy(node + sizeof(void *), data);

	list->head = node;
}

void _listPopFront(List *list)
{
	assert(list->head != NULL); //Список не должен быть пустым
	if (list->head == NULL) //На случай режима release, если assert не сработает
		return;
	void *newHead = *((void **) list->head); //Запоминаем новую голову
	//освобождаем память от выкидываемого элемента
	if (list->free != NULL) //Если пользователь задал функцию free, вызываем ее
		list->free(list->head + sizeof(void *));
	free(list->head);

	list->head = newHead;
}

void *_listFront(List *list)
{
	if (!list->head) //list is empty
		return NULL;
	return list->head + sizeof(void *);
}

void _listWalk(List *list, void (*cb)(void *data))
{
	assert(cb != NULL);
	void *node = list->head;
	while (node)
	{
		cb(node + sizeof(void *));
		node = *((void **)node);
	}
}

void _listClear(List *list)
{
	void *node = list->head;
	void *tempNode = NULL;
	while (node)
	{
		tempNode = *((void **)node); //Сохраняем заранее указатель на следующий элемент списка, пока не уничтожили текущий
		if (list->free != NULL) //Если пользователь задал функцию free, вызываем ее
			list->free(node + sizeof(void *)); //Освобождаем память, выделенную функцией list->cpy
		free(node); //Освобождаем память под сам узел
		node = tempNode;
	}
	list->head = NULL;	
}

void _listReverse(List *list)
{
	void *curNode = list->head; //Последний узел с провязанной в обратную сторону связью
	if (curNode == NULL)
		return; //Переворачивать нечего
	void *nextNode = *((void **) curNode);  //Следующий после curNode узел, возможно NULL. Нужно запоминать, так как связь в curNode указывает уже не на нужный узел 
	*((void **) curNode) = NULL; //Бывшая голова теперь первый элемент списка
	
	while (nextNode)
	{
		void *tempNode = *((void **) nextNode);
		*((void **) nextNode) = curNode;
		curNode = nextNode;
		nextNode = tempNode;
	}
	list->head = curNode; //Последний элемент последнего списка - новая голова
}

int _listEmpty(List *list)
{
	return (list->head) ? 0 : 1;
}
