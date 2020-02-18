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
	int (*cmp)(const void *arg1, const void *arg2); //!< Указатель на функцию сравнения двух элементов
	void (*free)(void *data); //!< Указатель на функцию для освобождения памяти, выделенной функцией cmp
} GList; //Нижнее подчеркивание нужно, чтобы корректно работало объявление List () list = ...

//init-destroy functions
#define newCustomList(type, cpyF, cmpF, freeF) _newCustomList(sizeof(type), cpyF, cmpF, freeF); //"Конструктор" для GList
GList *_newCustomList(size_t dataSize, void (*cpyFunc)(void *dst, const void *src), int (*cmpFunc)(const void *arg1, const void *arg2), void (*freeFunc)(void *data) );
void glistDestroy(GList *list);

//interface functions
void glistPushFront(GList *list, void *data);
void glistPopFront(GList *list);
void *glistFront(GList *list);
void glistWalk(GList *list, void (*cb)(void *data));
void glistClear(GList *list);
void glistReverse(GList *list);
int glistEmpty(GList *list);

#endif