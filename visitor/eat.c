/**
 * eat.c  2014-05-13
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
#include "eat.h"

static void eat_ops_dog_do_it(struct animal_do *animal_do, struct dog *dog)
{
	/* struct eat *a_eat = container_of(animal_do, typeof(*a_eat), animal_do);
	*/
	_MY_TRACE_STR("dog eat meal.\n");
}

static void eat_ops_cat_do_it(struct animal_do *animal_do, struct cat *cat)
{
	/* struct eat *a_eat = container_of(animal_do, typeof(*a_eat), animal_do);
	*/
	_MY_TRACE_STR("cat eat fish.\n");
}

static struct animal_do_ops animal_do_ops = {
	.dog_do_it = eat_ops_dog_do_it,
	.cat_do_it = eat_ops_cat_do_it,
};

/** constructor(). */
void eat_init(struct eat *eat)
{
	memset(eat, sizeof(*eat), 0);
	animal_do_init(&eat->animal_do);
	CLASS_OPS_INIT(eat->animal_do.ops, animal_do_ops);
}
