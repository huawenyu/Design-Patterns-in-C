/**
 * method_b.c  2014-05-19
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
 * Two different components have significant similarities, but demonstrate no
    reuse of common interface or implementation. If a change common to both
    components becomes necessary, duplicate effort must be expended.
 Intent:
    Define the skeleton of an algorithm in an operation, deferring some steps to client subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
    Base class declares algorithm 'placeholders', and derived classes implement the placeholders.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "method_b.h"

/** 2. Steps requiring peculiar implementations are "placeholders" in base
    class */
static void method_b_ops_step_2(struct template_method *template_method)
{
	/* struct method_b *a_method_b = container_of(template_method, typeof(*a_method_b), template_method);
	*/
	_MY_TRACE_STR("method_b::step_2()\n");
}

static void method_b_ops_step_4(struct template_method *template_method)
{
	/* struct method_b *a_method_b = container_of(template_method, typeof(*a_method_b), template_method);
	*/
	_MY_TRACE_STR("method_b::step_4()\n");
}

static struct template_method_ops template_method_ops = {
	.step_2 = method_b_ops_step_2,
	.step_4 = method_b_ops_step_4,
};

/** constructor(). */
void method_b_init(struct method_b *method_b)
{
	_MY_TRACE_STR("method_b_init()\n");
	memset(method_b, sizeof(*method_b), 0);
	template_method_init(&method_b->template_method);
	CLASS_OPS_INIT(method_b->template_method.ops, template_method_ops);
}