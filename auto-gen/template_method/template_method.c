/**
 * template_method.c  2014-05-19
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
#include "template_method.h"

static struct template_method_ops template_method_ops = {0
};

/** constructor(). */
void template_method_init(struct template_method *template_method)
{
	_MY_TRACE_STR("template_method_init()\n");
	memset(template_method, sizeof(*template_method), 0);
	template_method->ops = &template_method_ops;
}

void template_method_step_1(struct template_method *template_method)
{
	_MY_TRACE_STR("template_method::step_1()\n");
}

void template_method_step_3(struct template_method *template_method)
{
	_MY_TRACE_STR("template_method::step_3()\n");
}

void template_method_step_5(struct template_method *template_method)
{
	_MY_TRACE_STR("template_method::step_5()\n");
}
/** 1. Standardize the skeleton of an algorithm in a base class "template
    method" */
void template_method_execute(struct template_method *template_method)
{
	_MY_TRACE_STR("template_method::execute()\n");
	template_method_step_1(template_method);
	template_method_step_2(template_method);
	template_method_step_3(template_method);
	template_method_step_4(template_method);
	template_method_step_5(template_method);
}
