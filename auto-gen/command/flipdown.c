/**
 * flipdown.c  2014-05-19
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
#include "flipdown.h"

static void flipdown_ops_execute(struct command *command)
{
	struct flipdown *a_flipdown = container_of(command, typeof(*a_flipdown), command);
	
	_MY_TRACE_STR("flipdown::execute()\n");
	printf("turnoff %d\n", a_flipdown->_val);
	light_turnoff(a_flipdown->_light);
}

static struct command_ops command_ops = {
	.execute = flipdown_ops_execute,
};

/** constructor(). */
void flipdown_init(struct flipdown *flipdown, struct light *light, int val)
{
	_MY_TRACE_STR("flipdown_init()\n");
	memset(flipdown, sizeof(*flipdown), 0);
	command_init(&flipdown->command);
	CLASS_OPS_INIT(flipdown->command.ops, command_ops);
	flipdown->_light = light;
	flipdown->_val = val;
}
