/**
 * eat.h  2014-05-13
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
#ifndef __EAT_H__
#define __EAT_H__

#include <mycommon.h>
#include <mytrace.h>

#include "animal_do.h"

/** If we want to add make_sound() to our exists Animal-Heritance, How can we
    do:
1. we can add a new v-function to all our class-tree, 
2. Or we can use Visitor to add this new method outside of the exists class-tree. 
As Visitor, if oop language, we just need one v-function then use Visitor's overload to solve double dispatch, bur for C: 
1. we can assign diff enum class-type, when switch enum class-type to dispatch our call 
2. Or, we can provide serval v-functions, let the destination object choose from visitor's v-functions correctly to implement double dispatch. */
struct eat {
	struct animal_do animal_do;
};

/** constructor(). */
void eat_init(struct eat *eat);

#endif /* __EAT_H__ */