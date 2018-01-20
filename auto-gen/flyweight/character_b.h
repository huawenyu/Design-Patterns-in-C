/**
 * character_b.h  2014-05-19
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
#ifndef __CHARACTER_B_H__
#define __CHARACTER_B_H__

#include <mycommon.h>
#include <mytrace.h>

#include "character.h"

struct character_b {
	struct character character;
};

/** constructor(). */
void character_b_init(struct character_b *character_b);

#endif /* __CHARACTER_B_H__ */