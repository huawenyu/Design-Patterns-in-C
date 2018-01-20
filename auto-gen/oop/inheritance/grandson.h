/**
 * grandson.h  2014-05-03 15:06:28
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
#ifndef __GRANDSON_H__
#define __GRANDSON_H__

#include <mycommon.h>

#include "child.h"

struct grandson {
	struct child child;
};

void grandson_init(struct grandson *);

#endif /* __GRANDSON_H__ */