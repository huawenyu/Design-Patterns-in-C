/**
 * cat.c  2014-05-13
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
 * The Visitor pattern is in essence about covering an important use case of
    double dispatch in a single-dispatch language. It leverages the single-
    dispatch mechanism in a two-step idiom. Therefore if you use reflection for
    one of those two steps, you are no longer implementing Visitor. One way to
    look at it is that the visitor pattern is a way of letting your clients add
    additional methods to all of your classes in a particular class hierarchy.
    It is useful when you have a fairly stable class hierarchy, but you have
    changing requirements of what needs to be done with that hierarchy. The
    Visitor design pattern works really well for "recursive" structures like
    directory trees, XML structures, or document outlines.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "cat.h"
#include "animal_do.h"

static void cat_ops_do_it(struct animal *animal, struct animal_do *dome)
{
	struct cat *a_cat = container_of(animal, typeof(*a_cat), animal);
	_MY_TRACE_STR("cat::do_it()\n");
	animal_do_cat_do_it(dome, a_cat);
}

static struct animal_ops animal_ops = {
	.do_it = cat_ops_do_it,
};

/** constructor(). */
void cat_init(struct cat *cat)
{
	memset(cat, sizeof(*cat), 0);
	animal_init(&cat->animal);
	CLASS_OPS_INIT(cat->animal.ops, animal_ops);
}
