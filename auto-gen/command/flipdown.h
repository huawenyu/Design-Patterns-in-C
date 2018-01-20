/**
 * flipdown.h  2014-05-19
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
#ifndef __FLIPDOWN_H__
#define __FLIPDOWN_H__

#include <mycommon.h>
#include <mytrace.h>

#include "command.h"
#include "light.h"

struct flipdown {
	struct command command;
	struct light * _light;
	int _val;
};

/** constructor(). */
void flipdown_init(struct flipdown *flipdown, struct light *light, int val);

#endif /* __FLIPDOWN_H__ */
