#ifndef __CHAIN_HANDLE_H__
#define __CHAIN_HANDLE_H__

#include <stdio.h>
#include <stdlib.h>

#include <myobj.h>
#include <ulist.h>

struct chain_base_ops;
struct chain_handle
{
	struct chain_base_ops *ops;
	struct chain_handle *next; // 1. "next" pointer in the base class
};

struct chain_base_ops {
	void (*_add)(struct chain_handle *, struct chain_handle *next); /* not override */
	void (*handle)(struct chain_handle *, int);
	void (*close)(struct chain_handle *); /* virtual desturct routine, the base class no-implement */
	struct chain_base_ops *__super; /* should as last of ops, pointer to parent's ops */
};

void chain_base_init(struct chain_handle *base); /* construct routine */
struct chain_base_ops *chain_base_ops_get(struct chain_handle *base); /* base::ops */

static inline
void chain_base_add(struct chain_handle *base, struct chain_handle *next)
{
	base->ops->_add(base, next);
}

static inline
void chain_base_handle(struct chain_handle *base, int data)
{
	base->ops->handle(base, data);
}

static inline
void chain_base_close(struct chain_handle *base)
{
	base->ops->close(base);
}

static inline
void chain_base_close_super(struct chain_handle *base)
{
	base->ops->__super->close(base);
}

static inline
void chain_base_add_super(struct chain_handle *base, struct chain_handle *next)
{
	base->ops->__super->_add(base, next);
}

static inline
void chain_base_handle_super(struct chain_handle *base, int data)
{
	base->ops->__super->handle(base, data);
}

#endif /* __CHAIN_HANDLE_H__ */

