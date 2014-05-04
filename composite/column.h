/**
 * column.h  2014-05-04
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
#ifndef __COLUMN_H__
#define __COLUMN_H__

#include <mycommon.h>
#include <mytrace.h>

#include "composite.h"

struct column {
	struct composite composite;
};

void column_init(struct column *, int val);

#endif /* __COLUMN_H__ */