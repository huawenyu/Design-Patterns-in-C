/**
 * child.h  2014-05-03 06:45:54
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C
 */
#ifndef __CHILD_H__
#define __CHILD_H__

#include <mycommon.h>

#include "parent.h"

struct child_ops;

struct child {
	struct parent parent;
	struct child_ops *ops;
	int pub_data1;
	int pri_data2;
};
struct child_ops {
	struct child_ops *__super;
	int static_pub_data3;
	int static_pri_data4;
};
void child_init(struct child *);

#endif /* __CHILD_H__ */