/**
 * context.h  2014-05-17
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
 * Uses a class hierarchy to represent the grammar given.
 */
#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <mycommon.h>
#include <mytrace.h>

/** Hold the variable's eval value */
struct context {
	char _names[32][32];
	int _values[32];
};

/** constructor(). */
void context_init(struct context *context);

int context_get_value(struct context *context, char *name);
void context_put_value(struct context *context, char *name, int val);

#endif /* __CONTEXT_H__ */
