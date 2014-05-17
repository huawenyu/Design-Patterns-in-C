/**
 * data_node.h  2014-05-16
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
#ifndef __DATA_NODE_H__
#define __DATA_NODE_H__

#include <mycommon.h>
#include <mytrace.h>

/** the abstract data */
struct data_node {
	struct data_node* next; /** if array, point-to me */
};

/** constructor(). */
void data_node_init(struct data_node *data_node);

#endif /* __DATA_NODE_H__ */