/**
 * row.h  2014-05-04
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
#ifndef __ROW_H__
#define __ROW_H__

#include <mycommon.h>
#include <mytrace.h>

#include "composite.h"

struct row {
	struct composite composite;
};

void row_init(struct row *, int val);

#endif /* __ROW_H__ */