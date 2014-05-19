/**
 * command.h  2014-05-19
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
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <mycommon.h>
#include <mytrace.h>

struct command_ops;

struct command {
	struct command_ops *ops;
};
struct command_ops {
	void (*execute)(struct command *);
};

/** constructor(). */
void command_init(struct command *command);

static inline void command_execute(struct command *command)
{
	command->ops->execute(command);
}

#endif /* __COMMAND_H__ */