/**
 * iterator.c  2014-05-16
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C *
 * 
 * Add iterator to the container:
    - Design an "iterator" class for the "container" class
    - Add a createIterator() member to the container class
    - Clients ask the container object to create an iterator object
    - Clients use the first(), isDone(), next(), and currentItem() protocol
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "iterator.h"

static void iterator_ops_first(struct iterator *iterator)
{
	_MY_TRACE_STR("iterator::first()\n");
}

static void iterator_ops_next(struct iterator *iterator)
{
	_MY_TRACE_STR("iterator::next()\n");
}
/** return bool */
static int iterator_ops_is_end(struct iterator *iterator)
{
	_MY_TRACE_STR("iterator::is_end()\n");
	return 0;
}

static struct data_node * iterator_ops_current(struct iterator *iterator)
{
	_MY_TRACE_STR("iterator::current()\n");
	return 0;
}
static struct iterator_ops iterator_ops = {
	.first = iterator_ops_first,
	.next = iterator_ops_next,
	.is_end = iterator_ops_is_end,
	.current = iterator_ops_current,
};

/** constructor(). */
void iterator_init(struct iterator *iterator)
{
	_MY_TRACE_STR("iterator_init()\n");
	memset(iterator, sizeof(*iterator), 0);
	iterator->ops = &iterator_ops;
}