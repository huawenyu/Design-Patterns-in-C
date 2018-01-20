/**
 * template_method.h  2014-05-19
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
#ifndef __TEMPLATE_METHOD_H__
#define __TEMPLATE_METHOD_H__

#include <mycommon.h>
#include <mytrace.h>

struct template_method_ops;

struct template_method {
	struct template_method_ops *ops;
};
struct template_method_ops {
	void (*step_2)(struct template_method *); /** 2. Steps requiring peculiar implementations are "placeholders" in base
    class */
	void (*step_4)(struct template_method *);
};

/** constructor(). */
void template_method_init(struct template_method *template_method);

void template_method_step_1(struct template_method *template_method);

void template_method_step_3(struct template_method *template_method);

void template_method_step_5(struct template_method *template_method);
/** 1. Standardize the skeleton of an algorithm in a base class "template
    method" */
void template_method_execute(struct template_method *template_method);

/** 2. Steps requiring peculiar implementations are "placeholders" in base
    class */
static inline void template_method_step_2(struct template_method *template_method)
{
	template_method->ops->step_2(template_method);
}

static inline void template_method_step_4(struct template_method *template_method)
{
	template_method->ops->step_4(template_method);
}

#endif /* __TEMPLATE_METHOD_H__ */