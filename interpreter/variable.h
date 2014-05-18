/**
 * variable.h  2014-05-17
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
#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <mycommon.h>
#include <mytrace.h>

#include "operand.h"

/** <interface> */
struct variable {
	struct operand operand;
	char * _name;
};

/** constructor(). */
void variable_init(struct variable *variable, char *name);

#endif /* __VARIABLE_H__ */
