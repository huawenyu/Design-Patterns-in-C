/**
 * character_factory.c  2014-05-19
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

#include "character_factory.h"
#include "character_a.h"
#include "character_b.h"
#include "character_c.h"

/** constructor(). */
void character_factory_init(struct character_factory *character_factory)
{
	_MY_TRACE_STR("character_factory_init()\n");
	memset(character_factory, sizeof(*character_factory), 0);
}

struct character * character_factory_get_character(struct character_factory *fac, char c)
{
	struct character *val_char = 0;
	_MY_TRACE_STR("character_factory::get_character()\n");
	// Uses "lazy initialization"
	if (c > 'Z' || c < 'A')
		return 0;
	if (fac->_characters[c-'A'].c == c) {
		val_char = fac->_characters[c-'A'].val_char;
	}
	
	if (!val_char) {
		switch (c) {
		case 'A': {
			struct character_a *a;
			a = malloc(sizeof(*a));
			character_a_init(a);
			val_char = &a->character;
		} break;
		case 'B': {
			struct character_b *b;
			b = malloc(sizeof(*b));
			character_b_init(b);
			val_char = &b->character;
		} break;
		case 'C': {
			struct character_c *c2;
			c2 = malloc(sizeof(*c2));
			character_c_init(c2);
			val_char = &c2->character;
		} break;
		}
		fac->_characters[c-'A'].val_char = val_char;
	}
	return val_char;
}
