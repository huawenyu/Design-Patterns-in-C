/**
 * view.c  2014-05-14
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "view.h"

static void view_ops_update(struct observer *observer, char *operation, char *record)
{
	/* struct view *a_view = container_of(observer, typeof(*a_view), observer);
	*/
	_MY_TRACE_STR("view::update() with following:\n");
	printf("operation %s with %s\n", operation, record);
}

static struct observer_ops observer_ops = {
	.update = view_ops_update,
};

/** constructor(). */
void view_init(struct view *view)
{
	memset(view, sizeof(*view), 0);
	observer_init(&view->observer);
	CLASS_OPS_INIT(view->observer.ops, observer_ops);
}
