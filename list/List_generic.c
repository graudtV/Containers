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
	assert(list != NULL);
	assert(list->cpy != NULL && "list has been already destroyed or not initialised");
	glistClear(list);

	list->data_sz = 0;
	list->cpy = NULL;
	list->cmp = NULL;
	list->free = NULL;

	free(list); //!!!
	//printf("Freing list %p\n", list);
}

void glistAssign(GList *list, size_t count, const void *value)
{
	assert(list != NULL);
	assert(list->cpy != NULL);
	assert(value != NULL);
	glistClear(list);
	while (count--)
		glistPushFront(list, value);	
}

void glistPushFront(GList *list, const void *data)
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
	assert(list != NULL);
	assert(list->cpy != NULL);
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

void glistInsertAfter(GList *list, void *itPos, void *value)
{
	assert(list != NULL);
	assert(list->cpy != NULL);
	assert(itPos != NULL);
	assert(value != NULL);

	void *node = calloc(1, sizeof(void *) + list->data_sz); //выделяем память под новый узел
	assert(node != NULL);
	list->cpy(node + sizeof(void *), value);
	//Вставляем новый узел в список, изменяя связи
	*(void **) node = *(void **)(itPos - sizeof(void *)); //в node записываем указатель на продолжение списка
	*(void **)(itPos - sizeof(void *)) = node; //в созданный "разрыв" записываем указатель на node
}

void glistEraseAfter(GList *list, void *itPos)
{
	assert(list != NULL);
	assert(list->cpy != NULL);
	assert(itPos != NULL);

	void *node = *(void **) (itPos - sizeof(void *)); //Запоминаем указатель на удаляемый узел
	*(void **) (itPos - sizeof(void *)) = *(void **) node; //"Выбрасываем" удаляемый узел из списка
	//освобождаем память
	if (list->free)
		list->free(node + sizeof(void *));
	free(node);
}

void *glistFront(GList *list)
{
	assert(list != NULL);
	assert(list->cpy != NULL);

	if (!list->head) //list is empty
		return NULL;
	return list->head + sizeof(void *);
}

void glistRemove(GList *list, void *value)
{
	assert(list != NULL);
	assert(value != NULL);
	void **pnode = &list->head; //*pnode - текущий расматриваемый элемент. pnode - адрес, где записан указатель на этот элемент
	while (*pnode)
	{
		if ( list->cmp(*pnode + sizeof(void *), value) )
		{	//элемент НЕ совпал с value
			pnode = *pnode; //переходим к следующему узлу
			continue;
		}
		//Если данный элемент нужно удалить
		void *nextNode = *(void **) (*pnode); //Запоминаем указатель на следующий элемент
		if (list->free)
			list->free(*pnode + sizeof(void *));
		free(*pnode);
		*pnode = nextNode; //Записываем запомненный указатель
		continue;	
	}
}

void glistRemoveIf(GList *list, int (*criterionFunc) (const void *value))
{
	assert(list != NULL);
	assert(criterionFunc != NULL);
	//copied from glistRemove() this small changes
	void **pnode = &list->head; //*pnode - текущий расматриваемый элемент. pnode - адрес, где записан указатель на этот элемент
	while (*pnode)
	{
		//if ( list->cmp(*pnode + sizeof(void *), value) )
		if ( ! criterionFunc(*pnode + sizeof(void *)) )
		{	//элемент НЕ совпал с value
			pnode = *pnode; //переходим к следующему узлу
			continue;
		}
		//Если данный элемент нужно удалить
		void *nextNode = *(void **) (*pnode); //Запоминаем указатель на следующий элемент
		if (list->free)
			list->free(*pnode + sizeof(void *));
		free(*pnode);
		*pnode = nextNode; //Записываем запомненный указатель
		continue;	
	}	
}

void glistResize(GList *list, size_t newSize, void *defaultValue)
{
	assert(list != NULL);
	assert(list->cpy != NULL);
	assert(defaultValue != NULL);
	void **pnode = &list->head;
	while (newSize--)
	{
		if (!*pnode) //больше узлов нет
		{
		 	void *newNode = calloc(1, sizeof(void *) + list->data_sz);
		 	assert(newNode != NULL);
		 	list->cpy(newNode + sizeof(void *), defaultValue);
		 	*pnode = newNode; //добавляем созданный узел в конец(!) списка (вместо NULL)
		 	*(void **) newNode = NULL; //в новый узел записываем указатель на следующий, т.е. NULL, т.к. больше элементов нет. В принципе, это избыточно, т.к. calloc уже записал нули
		}
		pnode = *pnode; //переходим к следующему узлу
	}
	if (!*pnode) //список закончился раньше (newSize больше либо равен размеру списка)
		return;
	//если newSize оказался меньше размера списка
	*pnode = NULL; //указываем, что элементов в списке после данного больше нет
	//освобождаем память
	void *curNode = *pnode; //переменная для перебора узлов
	while (curNode) //пока не дошли до конца списка
	{
		void *nextNode = *(void **) curNode; //запоминаем следующий узел
		if (list->free)
			list->free(curNode + sizeof(void *));
		free(curNode);
		curNode = nextNode;
	}
}

void glistSwap(GList *list1, GList *list2) //swaps content and cmpFuncs. Other fields must be the same for both lists. No elements copied
{
	assert(list1 != NULL);
	assert(list2 != NULL);

	assert(list1->data_sz == list2->data_sz);
	assert(list1->cpy == list2->cpy);
	assert(list1->free == list2->free); //list->free may be NULL

	int (*cmpTemp)(const void *arg1, const void *arg2) = list1->cmp;
	list1->cmp = list2->cmp;
	list2->cmp = cmpTemp;

	void *headTemp = list1->head;
	list1->head = list2->head;
	list2->head = headTemp;
}

void glistClear(GList *list)
{
	assert(list != NULL);
	assert(list->cpy != NULL);

	void *node = list->head;
	while (node)
	{
		void *nextNode = *((void **)node); //Сохраняем заранее указатель на следующий элемент списка, пока не уничтожили текущий
		if (list->free != NULL) //Если пользователь задал функцию free, вызываем ее
			list->free(node + sizeof(void *)); //Освобождаем память, выделенную функцией list->cpy
		free(node); //Освобождаем память под сам узел
		//printf("freeing node %p (_listClear)\n", node);
		node = nextNode;
	}
	list->head = NULL;	
}

int glistEmpty(GList *list)
{
	return (list->head) ? 0 : 1;
}

void *glistItNext(void **pIt)
{
	assert(pIt != NULL);
	assert(*pIt != NULL); //cannot get the next element if this is the last element (NULL)
	*pIt = *(void **)(*pIt - sizeof(void *)); //ptr on the start of the next node (!) (not data)
	if (!*pIt) //ptr on the next node is NULL
		return NULL;
	return (*pIt += sizeof(void *)); //moving *pIt on start of data (находится через sizeof(void *) байт после начала узла)
}

void glistMerge(GList *list1, GList *list2)
{
	assert(list1 != NULL);
	assert(list2 != NULL);
	assert(list1->cpy != NULL);
	assert(list2->cpy != NULL);
	assert(list1->cmp != NULL);
	assert(list1->cmp == list2->cmp);
	if (list1 == list2)
		return;

	void *node1 = list1->head; //для перебора узлов списка 1
	void *node2 = list2->head; //для перебора узлов списка 1
	void **pnode = &list1->head; //указатель на последний записанный элемент
	while (node1 || node2) //пока не дойдем до конца в обоих списках
	{
		printf("node 1 = %p; val = %d\n", node1, *(int *)(node1 + sizeof(void *)));
		printf("node 2 = %p; val = %d\n", node2, *(int *)(node2 + sizeof(void *)));
		if ( node2 == NULL || ( node1 != NULL && list1->cmp(node1 + sizeof(void *), node2 + sizeof(void *)) < 0 ) ) //node1 < node2
		{
			//printf("cmp func res = %d\n", list1->cmp(node1 + sizeof(void *), node2 + sizeof(void *)));
			*pnode = node1; //приписываем к формируемому списку
			pnode = &node1;
			node1 = *(void **) node1;
		}
		else //node2 < node1
		{
			*pnode = node2;
			pnode = &node2;
			node2 = *(void **) node2;
		}
	}
	list2->head = NULL;
}

void glistUnique(GList *list)
{
	assert(list != NULL);
	assert(list->cpy != NULL);
	assert(list->cmp != NULL);
	void *prevNode = list->head;
	if (prevNode == NULL) //if there is less than 2 nodes
		return;
	void *curNode =  *(void **) prevNode;
	while (curNode)
	{
		if( ! list->cmp(prevNode + sizeof(void *), curNode + sizeof(void *)) )
		{	//2 last consecutive elements are equal
			*(void **) prevNode = *(void **) curNode; //в предыдущий узел перезаписываем указатель на следующий элемент
			if (list->free)
				list->free(curNode + sizeof(void *));
			free(curNode);
			curNode = *(void **) prevNode; //перемещаем curNode на следующий элемент списка
			continue;
		}
		//если совпадения не было, двигаем оба указателя вперед по списку
		curNode = *(void **) curNode;
		prevNode = *(void **) prevNode;
	}
}

void glistReverse(GList *list)
{
	assert(list != NULL);
	assert(list->cpy != NULL);

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

void glistSpliceAfter(void *itPos, GList *otherList)
{
	assert(itPos != NULL);
	assert(otherList != NULL);
	if (!otherList->head) //other list is empty
		return;

	void *tempNode = *(void **)(itPos - sizeof(void *)); //Запоминаем следующий после itPos элемент первого списка
	*(void **)(itPos - sizeof(void *)) = otherList->head; //Начинаем вставку otherList в исходный список
	void *node = otherList->head; //текущий рассматриваемый элемент в otherList
	//ищем конец второго списка
	while (*(void **) node) //пока следующий элемент - не NULL
		node = *(void **) node;
	//теперь node указывает на последний элемент списка 2
	*(void **) node = tempNode; //Заканчиваем вставку otherList в исходный список
	//меняем поля otherList
	otherList->head = NULL;
}
