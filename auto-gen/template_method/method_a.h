/**
 * method_a.h  2014-05-19
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
#ifndef __METHOD_A_H__
#define __METHOD_A_H__

#include <mycommon.h>
#include <mytrace.h>

#include "template_method.h"

/** 3. Derived classes implement placeholder methods */
struct method_a {
	struct template_method template_method;
};

/** constructor(). */
void method_a_init(struct method_a *method_a);

#endif /* __METHOD_A_H__ */