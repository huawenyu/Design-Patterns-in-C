/**
 * flipup.c  2014-05-19
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
 * The info will insert to every source file explaining the pattern's design details.
    We also can append lists like this:
      - list 1, give point one
          detail provide for point one
      - list 2, offer point two
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mycommon.h>
#include <myobj.h>
#include "flipup.h"

static void flipup_ops_execute(struct command *command)
{
	struct flipup *a_flipup = container_of(command, typeof(*a_flipup), command);
	
	_MY_TRACE_STR("flipup::execute()\n");
	printf("turnon %d\n", a_flipup->_val);
	light_turnon(a_flipup->_light);
}

static struct command_ops command_ops = {
	.execute = flipup_ops_execute,
};

/** constructor(). */
void flipup_init(struct flipup *flipup, struct light *light, int val)
{
	_MY_TRACE_STR("flipup_init()\n");
	memset(flipup, sizeof(*flipup), 0);
	command_init(&flipup->command);
	CLASS_OPS_INIT(flipup->command.ops, command_ops);
	flipup->_light = light;
	flipup->_val = val;
}
