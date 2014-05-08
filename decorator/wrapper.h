/**
 * wrapper.h  2014-05-08
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
#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include <mycommon.h>
#include <mytrace.h>

#include "decorator.h"

struct wrapper {
	struct decorator decorator;
};

/** constructor(). */
void wrapper_init(struct wrapper *wrapper, struct interface *inner, char *str);

#endif /* __WRAPPER_H__ */