/**
 * widget_one.c  2014-05-18
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
 * Use a mediator when the complexity of object communication begins to hinder object reusability.
    This type of complexity often appears in view instances, though it could really be anywhere.
    1. For example, using mediator to add log file functionality, it works like this:
      - Obj A tells the mediator it needs something done.
      - The mediator sends the message to various client objects.
      - Obj B does the thing Obj A needs, and sends an appropriate message back via the mediator.
      - Meanwhile, Obj C is also sent both messages by the mediator, and logs the results.
          That way, we can get user statistics from the log files.
      - Obj D could be an error checker as well, so that if Obj B responds that Obj A's request is impossible,
          Obj D could be the thing that reports that to the user.
          Errors can now be logged in a different file than regular activity,
          and could use some other means to behave (beeping, whatever) that Obj A shouldn't really concern itself with.

    2. The following code assume that:
      At a highlevel, we have 2 Participants that want to talk so we need to setup a common interface to do so.
      - We create a method call Notify(message); that basically is our channel of communication.
      - To set things up we instantiate a mediator, and then instantiate both participants passing them the mediator.
      - The last step insetup, is to inject/set the mediators participants. In our case we just use simple setters.
      - When its time to communicate, each participant just calls the mediator, passes the message and self as a parameter.
      - Mediator see who contacted them, and then calls the opposite.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "widget_one.h"
#include "mediator.h"

/** forward to instance's self task, here is talk */
static char * widget_one_ops_notify(struct participant *participant, char *msg)
{
	struct widget_one *a_widget_one = container_of(participant, typeof(*a_widget_one), participant);
	
	static char response[] = "This is response message from widget_one.";
	_MY_TRACE_STR("widget_one::notify()\n");
	printf("widget_one receive: %s\n", msg);
	return response;
}

static struct participant_ops participant_ops = {
	.notify = widget_one_ops_notify,
};

/** constructor(). */
void widget_one_init(struct widget_one *widget_one, struct mediator *mediator)
{
	_MY_TRACE_STR("widget_one_init()\n");
	memset(widget_one, sizeof(*widget_one), 0);
	participant_init(&widget_one->participant);
	CLASS_OPS_INIT(widget_one->participant.ops, participant_ops);
	widget_one->_mediator = mediator;
}

/** forward to mediator */
char * widget_one_talk(struct widget_one *widget_one, char *msg)
{
	_MY_TRACE_STR("widget_one::talk()\n");
	return mediator_talk(widget_one->_mediator, &widget_one->participant, msg);
}
