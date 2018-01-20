/**
 * light.c  2014-05-19
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

#include "light.h"

/** constructor(). */
void light_init(struct light *light)
{
	_MY_TRACE_STR("light_init()\n");
	memset(light, sizeof(*light), 0);
}

void light_turnon(struct light *light)
{
	_MY_TRACE_STR("light::turnon()\n");
}

void light_turnoff(struct light *light)
{
	_MY_TRACE_STR("light::turnoff()\n");
}