/**
 * context.c  2014-05-17
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>

#include "context.h"

/** constructor(). */
void context_init(struct context *context)
{
	_MY_TRACE_STR("context_init()\n");
	memset(context, sizeof(*context), 0);
}

int context_get_value(struct context *context, char *name)
{
	int ii;
	_MY_TRACE_STR("context::get_value()\n");
	for (ii=0; ii<32; ii++) {
		if (0 == strcmp(context->_names[ii], name))
			return context->_values[ii];
	}
	return 0;
}

void context_put_value(struct context *context, char *name, int val)
{
	int ii;
	_MY_TRACE_STR("context::get_value()\n");
	for (ii=0; ii<32; ii++) {
		if (0 == strcmp(context->_names[ii], name)) {
			context->_values[ii] = val;
			return;
		}
	}
	for (ii=0; ii<32; ii++) {
		if (!context->_names[ii][0]) {
			snprintf(context->_names[ii], sizeof(context->_names[ii]), name);
			context->_values[ii] = val;
			return;
		}
	}
}

