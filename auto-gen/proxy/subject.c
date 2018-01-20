/**
 * subject.c  2014-05-19
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
 * Provides a surrogate or placeholder for another object to control access to
    it.This structural code demonstrates the Proxy pattern which provides a
    representative object (proxy) that controls access to another similar
    object.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "subject.h"

static struct subject_ops subject_ops = {0
};

/** constructor(). */
void subject_init(struct subject *subject)
{
	_MY_TRACE_STR("subject_init()\n");
	memset(subject, sizeof(*subject), 0);
	subject->ops = &subject_ops;
}