/**
 * character_c.c  2014-05-19
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
 * The Flyweight pattern is used to avoid the overhead of large numbers of
    very similar classes. There are cases in programming where it seems that
    you need to generate a very large number of small class instances to
    represent data. Sometimes you can greatly reduce the number of different
    classes that you need to instantiate if you can recognize that the
    instances are fundamentally the same except for a few parameters. If you
    can move those variables outside the class instance and pass them in as
    part of a method call, the number of separate instances can be greatly
    reduced by sharing them.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "character_c.h"

static void character_c_ops_display(struct character *character, int size)
{
	/* struct character_c *a_character_c = container_of(character, typeof(*a_character_c), character);
	*/
	_MY_TRACE_STR("character_c::display()\n");
}

static struct character_ops character_ops = {
	.display = character_c_ops_display,
};

/** constructor(). */
void character_c_init(struct character_c *character_c)
{
	_MY_TRACE_STR("character_c_init()\n");
	memset(character_c, sizeof(*character_c), 0);
	character_init(&character_c->character);
	CLASS_OPS_INIT(character_c->character.ops, character_ops);
}
