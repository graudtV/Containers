/*!
 * \file
 * \brief Реализация односвязного списка для произвольного типа данных на чистом C
 */
#ifndef _LIST_H_
#define _LIST_H_

#include "List_generic.h"
#include "List_int.h"

//Для удобной работы со списками разных типов определения функций приходится делать в виде макросов
#define List(type) List_##type
#define List_custom List_
//init-destroy functions
#define newCustomList(type, cpyF, cmpF, freeF) _newCustomList(sizeof(type), cpyF, cmpF, freeF); //"Конструктор" непосредственно для List_ (произвольного типа)
#define newList(type) _Generic(((type) 0), int: _newList_int())
#define listDestroy(plist) _Generic((plist), List_ *: _listDestroy, List_int *: _listDestroy)((List_ *) plist) //Использование обычного макроса без проверки типа опасно, так как можно передать void * NULL и компилятор не выдаст ошибки, так как есть явное приведение типа

//interface functions
#define listPushFront(plist, pdata) _Generic((plist), List_ *: _listPushFront, List_int *: _listPushFront_int)(plist, pdata)
#define listPopFront(plist) _Generic((plist), List_ *: _listPopFront, List_int *: _listPopFront)((List_ *) plist)
#define listFront(plist) _Generic((plist), List_ *: _listFront((List_ *) plist), List_int *: *(int *) _listFront((List_ *) plist)) //Возвращает первый элемент
#define listWalk(plist, pCallBackFunc) _Generic((plist), List_ *: _listWalk(plist, pCallBackFunc))
#define listClear(plist) _Generic((plist), List_ *: _listClear, List_int *: _listClear)((List_ *) plist)
#define listReverse(plist) _Generic((plist), List_ *: _listReverse, List_int *: _listReverse)((List_ *) plist)
#define listEmpty(plist) _Generic((plist), List_ *: _listEmpty, List_int *: _listEmpty)((List_ *) plist)


#endif // _LIST_H_