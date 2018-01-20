/**
 * real_subject.c  2014-05-19
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
#include "real_subject.h"

static void real_subject_ops_request(struct subject *subject)
{
	/* struct real_subject *a_real_subject = container_of(subject, typeof(*a_real_subject), subject);
	*/
	_MY_TRACE_STR("real_subject::request()\n");
}

static struct subject_ops subject_ops = {
	.request = real_subject_ops_request,
};

/** constructor(). */
void real_subject_init(struct real_subject *real_subject)
{
	_MY_TRACE_STR("real_subject_init()\n");
	memset(real_subject, sizeof(*real_subject), 0);
	subject_init(&real_subject->subject);
	CLASS_OPS_INIT(real_subject->subject.ops, subject_ops);
}