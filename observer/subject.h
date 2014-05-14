/**
 * subject.h  2014-05-14
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
#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <mycommon.h>
#include <mytrace.h>

#include "observer.h"

struct subject_ops;

struct subject {
	struct subject_ops *ops;
	struct observer * obs[32];
	int obs_sz;
};
struct subject_ops {
	int (*register_observer)(struct subject *, struct observer *obs);
	int (*remove_observer)(struct subject *, struct observer *obs);
	int (*notify_observers)(struct subject *, char *operation, char *record);
	struct subject_ops *__super;
};

/** constructor(). */
void subject_init(struct subject *subject);

static inline int subject_register_observer(struct subject *subject, struct observer *obs)
{
	return subject->ops->register_observer(subject, obs);
}

static inline int subject_remove_observer(struct subject *subject, struct observer *obs)
{
	return subject->ops->remove_observer(subject, obs);
}

static inline int subject_notify_observers(struct subject *subject, char *operation, char *record)
{
	return subject->ops->notify_observers(subject, operation, record);
}

#endif /* __SUBJECT_H__ */
