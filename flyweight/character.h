/**
 * character.h  2014-05-19
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
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <mycommon.h>
#include <mytrace.h>

struct character_ops;

struct character {
	struct character_ops *ops;
	char symbol;
	int size;
	int width;
	int height;
};
struct character_ops {
	void (*display)(struct character *, int size);
};

/** constructor(). */
void character_init(struct character *character);

static inline void character_display(struct character *character, int size)
{
	character->ops->display(character, size);
}

#endif /* __CHARACTER_H__ */
