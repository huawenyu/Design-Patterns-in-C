/**
 * me.h  2014-05-14
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
#ifndef __ME_H__
#define __ME_H__

#include <mycommon.h>
#include <mytrace.h>

#include "A_B1.h"
#include "A_B2.h"
#include "A_B3.h"
#include "M_N.h"
#include "P_Q.h"

struct me {
	struct A_B1 A_B1;
	struct A_B2 A_B2;
	struct A_B3 A_B3;
	struct M_N M_N;
	struct P_Q P_Q;
};

/** constructor(). */
void me_init(struct me *me);

#endif /* __ME_H__ */
