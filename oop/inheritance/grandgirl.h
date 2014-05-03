/**
 * grandgirl.h  2014-05-03 06:45:54
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
#ifndef __GRANDGIRL_H__
#define __GRANDGIRL_H__

#include <mycommon.h>

#include "child.h"

struct grandgirl {
	struct child child;
};

void grandgirl_init(struct grandgirl *);

#endif /* __GRANDGIRL_H__ */