/**
 * observer.h  2014-05-14
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
 * The Observer Pattern (sometimes called Listener Pattern) is a design
    pattern which establishes a one-to-many relationship between objects, such
    that changes to one object (the subject) may be communicated to many other
    objects (the observers/listeners). The power of this pattern is that it
    loosely couples objects together in a manner that does not require the
    subject or its listeners understanding anything about the other, beyond the
    fact that they implement a shared interface for communicating.
 */
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <mycommon.h>
#include <mytrace.h>

struct observer_ops;
/** As listener, we can have many this kind objects. */
struct observer {
	struct observer_ops *ops;
};
struct observer_ops {
	void (*update)(struct observer *, char *operation, char *record);
};

/** constructor(). */
void observer_init(struct observer *observer);

static inline void observer_update(struct observer *observer, char *operation, char *record)
{
	observer->ops->update(observer, operation, record);
}

#endif /* __OBSERVER_H__ */