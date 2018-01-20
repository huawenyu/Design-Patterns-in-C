/**
 * P_Q.h  2014-05-14
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
#ifndef __P_Q_H__
#define __P_Q_H__

#include <mycommon.h>
#include <mytrace.h>

#include "P.h"

/** show pure virtual */
struct P_Q {
	struct P P;
};

/** constructor(). */
void P_Q_init(struct P_Q *P_Q);

#endif /* __P_Q_H__ */