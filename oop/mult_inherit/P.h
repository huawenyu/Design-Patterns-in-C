/**
 * P.h  2014-05-14
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
#ifndef __P_H__
#define __P_H__

#include <mycommon.h>
#include <mytrace.h>

struct P_ops;
/** show pure virtual */
struct P {
	struct P_ops *ops;
};
struct P_ops {
	void (*_destructor)(struct P *); /** called by free(): put resources, forward to super. */
	void (*free)(struct P *); /** free memory after call destructor(). */
	void (*jump_up)(struct P *);
	void (*jump_down)(struct P *);
	struct P_ops *__super;
};

/** constructor(). */
void P_init(struct P *P);

/** called by free(): put resources, forward to super. */
static inline void P__destructor(struct P *P)
{
	P->ops->_destructor(P);
}
/** free memory after call destructor(). */
static inline void P_free(struct P *P)
{
	P->ops->free(P);
}

static inline void P_jump_up(struct P *P)
{
	P->ops->jump_up(P);
}

static inline void P_jump_down(struct P *P)
{
	P->ops->jump_down(P);
}

#endif /* __P_H__ */