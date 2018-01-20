/**
 * M_N.h  2014-05-14
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
#ifndef __M_N_H__
#define __M_N_H__

#include <mycommon.h>
#include <mytrace.h>

#include "M.h"

/** show none-override */
struct M_N {
	struct M M;
};

/** constructor(). */
void M_N_init(struct M_N *M_N);

#endif /* __M_N_H__ */