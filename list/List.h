/*!
 * \file
 * \brief Реализация односвязного списка для произвольного типа данных на чистом C
 */
#ifndef _LIST_H_
#define _LIST_H_

#include "List_generic.h"
#include "List_int.h"
#include "List_char.h"

//Для удобной работы со списками разных типов определения функций приходится делать в виде макросов
#define List(type) List_##type
#define List_custom GList
//init-destroy functions
#define newList(type) _newList_##type()
//#define newList(type) _Generic(((type) 0), int: _newList_int, char: _newList_char)()
#define listDestroy(plist) _Generic((plist), GList *: glistDestroy, List_int *: glistDestroy, List_char *: glistDestroy)((GList *) plist) //Использование обычного макроса без проверки типа опасно, так как можно передать void * NULL и компилятор не выдаст ошибки, так как есть явное приведение типа

//interface functions
#define listPushFront(plist, pdata) _Generic((plist), GList *: glistPushFront, List_int *: _listPushFront_int, List_char *: _listPushFront_char)(plist, pdata)
#define listPopFront(plist) _Generic((plist), GList *: glistPopFront, List_int *: _listPopFront_int, List_char *: _listPopFront_char)(plist)
#define listFront(plist) _Generic((plist), GList *: glistFront((GList *) plist), List_int *: *(int *) glistFront((GList *) plist), List_char *: *(char *) glistFront((GList *) plist)) //Возвращает первый элемент
#define listWalk(plist, pCallBackFunc) _Generic((plist), GList *: glistWalk(plist, pCallBackFunc))
#define listClear(plist) _Generic((plist), GList *: glistClear, List_int *: glistClear, List_char *: glistClear)((GList *) plist)
#define listReverse(plist) _Generic((plist), GList *: glistReverse, List_int *: glistReverse, List_char *: glistReverse)((GList *) plist)
#define listEmpty(plist) _Generic((plist), GList *: glistEmpty, List_int *: glistEmpty, List_char *: glistEmpty)((GList *) plist)


#endif // _LIST_H_