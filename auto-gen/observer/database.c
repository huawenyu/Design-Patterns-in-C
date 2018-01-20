/**
 * database.c  2014-05-14
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
#include "database.h"

static struct subject_ops subject_ops = {0
};
/** constructor(). */
void database_init(struct database *database)
{
	memset(database, sizeof(*database), 0);
	subject_init(&database->subject);
	CLASS_OPS_INIT_SUPER(database->subject.ops, subject_ops);
}

void database_edit_record(struct database *database, char *operation, char *record)
{
	_MY_TRACE_STR("database::edit_record()\n");
	subject_notify_observers(&database->subject, operation, record);
}
