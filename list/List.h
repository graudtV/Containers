/*!
 * \file
 * \brief Реализация односвязного списка для произвольного типа данных на чистом C
 */
#ifndef _LIST_H_
#define _LIST_H_

#include "List_generic.h"
#include "List_int.h"

//Для удобной работы со списками разных типов определения функций приходится делать в виде макросов
//init-destroy functions
#define newCustomList(type, cpyF, cmpF, freeF) _newCustomList(sizeof(type), cpyF, cmpF, freeF); //"Конструктор" непосредственно для List (произвольного типа)
#define newList(type) _Generic(((type) 0), int: _newIntList())
#define listDestroy(plist) _Generic((plist), List *: _listDestroy((List *) plist), ListInt*: _listIntDestroy((ListInt *) plist))

//interface functions
#define listPushFront(plist, pdata) _Generic((plist), List *: _listPushFront(plist, pdata))
#define listPopFront(plist) _Generic((plist), List *: _listPopFront(plist))
#define listFront(plist) _Generic((plist), List *: _listFront(plist)) //Возвращает первый элемент
#define listWalk(plist, pCallBackFunc) _Generic((plist), List *: _listWalk(plist, pCallBackFunc))
#define listClear(plist) _Generic((plist), List *: _listClear(plist))
#define listReverse(plist) _Generic((plist), List *: _listReverse(plist))
#define listEmpty(plist) _Generic((plist), List *: _listEmpty(plist))


#endif // _LIST_H_