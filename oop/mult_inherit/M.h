/**
 * M.h  2014-05-14
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
#ifndef __M_H__
#define __M_H__

#include <mycommon.h>
#include <mytrace.h>

struct M_ops;
/** show none-override */
struct M {
	struct M_ops *ops;
};
struct M_ops {
	void (*_destructor)(struct M *); /** called by free(): put resources, forward to super. */
	void (*free)(struct M *); /** free memory after call destructor(). */
	void (*put_here)(struct M *);
	void (*put_there)(struct M *);
	struct M_ops *__super;
};

/** constructor(). */
void M_init(struct M *M);

/** called by free(): put resources, forward to super. */
static inline void M__destructor(struct M *M)
{
	M->ops->_destructor(M);
}
/** free memory after call destructor(). */
static inline void M_free(struct M *M)
{
	M->ops->free(M);
}

static inline void M_put_here(struct M *M)
{
	M->ops->put_here(M);
}

static inline void M_put_there(struct M *M)
{
	M->ops->put_there(M);
}

#endif /* __M_H__ */