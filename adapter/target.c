
/**
 * target.c  2014-04-29 05:44:08
 * anonymouse(anonymouse@email)
 *
 * Copyright (C) 2000-2014 All Right Reserved
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Auto generate for Design Patterns in C
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "target.h"


static void target_ops_request(struct target *target)
{
	printf("target::request()\n");
}
static struct target_ops target_ops = {
	.request = target_ops_request,
};

void target_init(struct target *target)
{
	memset(target, sizeof(*target), 0);
	target->ops = &target_ops;
}

