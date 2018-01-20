/**
 * caculator.h  2014-05-17
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
 * Uses a class hierarchy to represent the grammar given.
 */
#ifndef __CACULATOR_H__
#define __CACULATOR_H__

#include <mycommon.h>
#include <mytrace.h>

#include "variable.h"
		
#include "expression.h"
		
#include "number.h"

struct caculator {
};

/** constructor(). */
void caculator_init(struct caculator *caculator);

/** return bool */
int caculator_precedence(char a, char b);
/** convert expr from in-fix to post-fix */
char * caculator_convert_to_postfix(char *);

struct operand * caculator_build_syntax_tree(char *);

#endif /* __CACULATOR_H__ */
