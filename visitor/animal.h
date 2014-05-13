/**
 * animal.h  2014-05-13
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
#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include <mycommon.h>
#include <mytrace.h>

struct animal_do;
struct animal_ops;
/** forward declare struct animal_do */
struct animal {
	struct animal_ops *ops;
};
struct animal_ops {
	void (*do_it)(struct animal *, struct animal_do *dome);
};

/** constructor(). */
void animal_init(struct animal *animal);

static inline void animal_do_it(struct animal *animal, struct animal_do *dome)
{
	animal->ops->do_it(animal, dome);
}

#endif /* __ANIMAL_H__ */
