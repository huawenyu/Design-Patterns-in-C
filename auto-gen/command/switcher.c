/**
 * switcher.c  2014-05-19
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

#include "switcher.h"
#include "command.h"

/** constructor(). */
void switcher_init(struct switcher *switcher)
{
	_MY_TRACE_STR("switcher_init()\n");
	memset(switcher, sizeof(*switcher), 0);
}

void switcher_append(struct switcher *switcher, struct command *cmd)
{
	_MY_TRACE_STR("switcher::append()\n");
	switcher->_commands[switcher->_commands_sz++] = cmd;
}

void switcher_execute(struct switcher *switcher)
{
	int i;
	_MY_TRACE_STR("switcher::execute()\n");
	for (i=0; i < switcher->_commands_sz; i++) {
		command_execute(switcher->_commands[i]);
	}
}
