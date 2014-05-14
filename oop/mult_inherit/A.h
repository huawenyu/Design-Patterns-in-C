/**
 * A.h  2014-05-14
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
#ifndef __A_H__
#define __A_H__

#include <mycommon.h>
#include <mytrace.h>

struct A_ops;
/** show override */
struct A {
	struct A_ops *ops;
};
struct A_ops {
	void (*_destructor)(struct A *); /** called by free(): put resources, forward to super. */
	void (*free)(struct A *); /** free memory after call destructor(). */
	void (*do_this)(struct A *);
	void (*do_that)(struct A *);
	struct A_ops *__super;
};

/** constructor(). */
void A_init(struct A *A);

/** called by free(): put resources, forward to super. */
static inline void A__destructor(struct A *A)
{
	A->ops->_destructor(A);
}
/** free memory after call destructor(). */
static inline void A_free(struct A *A)
{
	A->ops->free(A);
}

static inline void A_do_this(struct A *A)
{
	A->ops->do_this(A);
}

static inline void A_do_that(struct A *A)
{
	A->ops->do_that(A);
}

#endif /* __A_H__ */