#include "List.h"
#include <stdlib.h>
#include <assert.h>

GList *_newCustomList(size_t dataSize, void (*cpyFunc)(void *dst, const void *src),
					int (*cmpFunc)(const void *arg1, const void *arg2), void (*freeFunc)(void *data) )
{
	assert(cpyFunc != NULL);	
	GList *list = calloc(1, sizeof(GList));
	assert(list != NULL);
	//printf("New list %p size %zu\n", list, sizeof(GList));
	//Инициализация значениями
	list->head = NULL;
	list->data_sz = dataSize;
	list->cpy = cpyFunc;
	list->cmp = cmpFunc;
	list->free = freeFunc;

	return list;
}

void glistDestroy(GList *list)
{
	glistClear(list);

	list->data_sz = 0;
	list->cpy = NULL;
	list->cmp = NULL;
	list->free = NULL;

	free(list); //!!!
	//printf("Freing list %p\n", list);
}



void glistPushFront(GList *list, void *data)
{
	assert(list != NULL);
	assert(data != NULL);
	assert(list->cpy != NULL);

	void *node = calloc(1, sizeof(void *) + list->data_sz);
	//printf("New node %p size %zu\n", node, sizeof(void *) + list->data_sz);
	assert(node != NULL);
	//Инициализация нового элемента списка ("узла")
	*((void **) node) = list->head; //в поле next новой головы записываем указатель на старую
	list->cpy(node + sizeof(void *), data);

	list->head = node;
}

void glistPopFront(GList *list)
{
	assert(list->head != NULL); //Список не должен быть пустым
	if (list->head == NULL) //На случай режима release, если assert не сработает
		return;
	void *newHead = *((void **) list->head); //Запоминаем новую голову
	//освобождаем память от выкидываемого элемента
	if (list->free != NULL) //Если пользователь задал функцию free, вызываем ее
		list->free(list->head + sizeof(void *));
	free(list->head);
	////printf("freeing node %p\n", list->head);
	list->head = newHead;
}

void *glistFront(GList *list)
{
	if (!list->head) //list is empty
		return NULL;
	return list->head + sizeof(void *);
}

void glistWalk(GList *list, void (*cb)(void *data))
{
	assert(cb != NULL);
	void *node = list->head;
	while (node)
	{
		cb(node + sizeof(void *));
		node = *((void **)node);
	}
}

void glistClear(GList *list)
{
	void *node = list->head;
	void *tempNode = NULL;
	while (node)
	{
		tempNode = *((void **)node); //Сохраняем заранее указатель на следующий элемент списка, пока не уничтожили текущий
		if (list->free != NULL) //Если пользователь задал функцию free, вызываем ее
			list->free(node + sizeof(void *)); //Освобождаем память, выделенную функцией list->cpy
		free(node); //Освобождаем память под сам узел
		//printf("freeing node %p (_listClear)\n", node);
		node = tempNode;
	}
	list->head = NULL;	
}

void glistReverse(GList *list)
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

int glistEmpty(GList *list)
{
	return (list->head) ? 0 : 1;
}
