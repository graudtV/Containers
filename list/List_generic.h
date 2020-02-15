/*!
 * \file
 * \brief Прототипы функций для работы со списком с произвольным типом данных
 */
#ifndef _LISTGENERIC_H_
#define _LISTGENERIC_H_


#include <stdio.h> //для size_t

typedef struct
{
	void *head; //!< Указатель на первый элемент списка
	size_t data_sz; //!< Размер типа данных, записываемых в список
	void (*cpy)(void *dst, const void *src); //!< Указатель на функцию, которая копирует нужным образом элемент в список (возможно, с выделение памяти, например, под строки)
	void (*cmp)(const void *arg1, const void *arg2); //!< Указатель на функцию сравнения двух элементов
	void (*free)(void *data); //!< Указатель на функцию для освобождения памяти, выделенной функцией cmp
} List;

//init-destroy functions
List *_newCustomList(size_t dataSize, void (*cpyFunc)(void *dst, const void *src), void (*cmpFunc)(const void *arg1, const void *arg2), void (*freeFunc)(void *data) );
void _listDestroy(List *list);

//interface functions
void _listPushFront(List *list, void *data);
void _listPopFront(List *list);
void *_listFront(List *list);
void _listWalk(List *list, void (*cb)(void *data));
void _listClear(List *list);
void _listReverse(List *list);
int _listEmpty(List *list);

#endif