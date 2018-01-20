/**
 * character_factory.h  2014-05-19
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
#ifndef __CHARACTER_FACTORY_H__
#define __CHARACTER_FACTORY_H__

#include <mycommon.h>
#include <mytrace.h>
#include "character.h"

struct character_dict {
	char c;
	struct character *val_char;
};
struct character_factory {
	struct character_dict _characters['Z'-'A'+1];
};

/** constructor(). */
void character_factory_init(struct character_factory *character_factory);

struct character * character_factory_get_character(struct character_factory *character_factory, char c);

#endif /* __CHARACTER_FACTORY_H__ */
