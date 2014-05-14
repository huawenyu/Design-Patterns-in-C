/**
 * A_B1.h  2014-05-14
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
#ifndef __A_B1_H__
#define __A_B1_H__

#include <mycommon.h>
#include <mytrace.h>

#include "A.h"

/** show override */
struct A_B1 {
	struct A A;
};

/** constructor(). */
void A_B1_init(struct A_B1 *A_B1);

#endif /* __A_B1_H__ */