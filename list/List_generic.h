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
} GList;

//init-destroy functions
#define newCustomList(type, cpyF, cmpF, freeF) _newCustomList(sizeof(type), cpyF, cmpF, freeF); //"Конструктор" для GList
GList *_newCustomList(size_t dataSize, void (*cpyFunc)(void *dst, const void *src), int (*cmpFunc)(const void *arg1, const void *arg2), void (*freeFunc)(void *data) );
void glistDestroy(GList *list);

//interface functions
void glistPushFront(GList *list, void *data);
void glistPopFront(GList *list);
void *glistFront(GList *list); //ptr on data of the front element
void *glistFind(GList *list, void *data);
void glistClear(GList *list);
int glistEmpty(GList *list);
	//iteration
#define glistBegin(plist) glistFront(plist) //for GList glistBegin() is equal to glistFront()
void *glistItNext(void **pIt); // analog for "it++" in C++. Gets ptr on the iterator. "end" in C++ is equal to NULL here

	//operations
void glistUnique(GList *list); //Removes all consecutive duplicate elements from the list
void glistReverse(GList *list);
void glistSpliceAfter(void *itPos, GList *otherList); //inserts elements from otherList after an element in some list. The element is pointed by itPos. No elements copied. If lists have different types the behaviour is undefined.

#endif